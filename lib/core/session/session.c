#define _POSIX_C_SOURCE 200809L

#include <yai/core/session.h>
#include "yai_session_internal.h"
#include <yai/api/runtime.h>
#include <yai/core/workspace.h>
#include <yai/law/resolver.h>
#include <yai/law/policy_effects.h>

#include <transport.h>
#include <protocol.h>

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <yai_protocol_ids.h>

/* Global in-process session registry. */

yai_session_t g_session_registry[MAX_SESSIONS] = {0};

/* Internal helpers. */

static const char *yai_get_home(void)
{
    const char *home = getenv("HOME");
    return (home && strlen(home) > 0) ? home : NULL;
}

static int mkdir_if_missing(const char *path, mode_t mode)
{
    struct stat st;
    if (stat(path, &st) == 0)
        return S_ISDIR(st.st_mode) ? 0 : -1;

    return mkdir(path, mode);
}

static int ensure_run_tree(const char *home)
{
    char p1[MAX_PATH_LEN], p2[MAX_PATH_LEN];

    snprintf(p1, sizeof(p1), "%s/.yai", home);
    snprintf(p2, sizeof(p2), "%s/.yai/run", home);

    if (mkdir_if_missing(p1, 0755) != 0)
        return -1;
    if (mkdir_if_missing(p2, 0755) != 0)
        return -1;

    return 0;
}


/* Workspace path/state helpers. */

bool yai_ws_validate_id(const char *ws_id)
{
    return yai_ws_id_is_valid(ws_id);
}

bool yai_ws_build_paths(yai_workspace_t *ws, const char *ws_id)
{
    const char *home = yai_get_home();
    time_t now = time(NULL);
    if (!ws || !home || !yai_ws_validate_id(ws_id))
        return false;

    memset(ws, 0, sizeof(*ws));

    strncpy(ws->ws_id, ws_id, MAX_WS_ID_LEN - 1);

    snprintf(ws->run_dir, MAX_PATH_LEN,
             "%s/.yai/run/%s", home, ws_id);

    snprintf(ws->root_path, MAX_PATH_LEN,
             "%s/.yai/workspaces/%s", home, ws_id);

    snprintf(ws->lock_file, MAX_PATH_LEN,
             "%s/lock", ws->run_dir);

    snprintf(ws->pid_file, MAX_PATH_LEN,
             "%s/runtime.pid", ws->run_dir);

    snprintf(ws->ingress_sock, MAX_PATH_LEN,
             "%s/%s", home, YAI_RUNTIME_INGRESS_SOCKET_REL);

    ws->created_at = (long)now;
    ws->updated_at = (long)now;
    ws->state = YAI_WS_ACTIVE;
    return true;
}

/* Session acquire/release lifecycle. */

bool yai_session_acquire(yai_session_t **out, const char *ws_id)
{
    if (!out || !ws_id)
        return false;

    /* Fast path: return an already-active session for the workspace. */

    for (int i = 0; i < MAX_SESSIONS; i++)
    {
        if (g_session_registry[i].owner_pid != 0 &&
            strcmp(g_session_registry[i].ws.ws_id, ws_id) == 0)
        {
            *out = &g_session_registry[i];
            return true;
        }
    }

    /* Allocate a new slot when no active session is found. */

    for (int i = 0; i < MAX_SESSIONS; i++)
    {
        if (g_session_registry[i].owner_pid == 0)
        {
            yai_workspace_t ws;

            if (!yai_ws_build_paths(&ws, ws_id))
                return false;

            ensure_run_tree(yai_get_home());
            mkdir_if_missing(ws.run_dir, 0755);

            int fd = open(ws.lock_file,
                          O_CREAT | O_EXCL | O_RDWR,
                          0600);

            if (fd < 0)
            {
                if (errno == EEXIST)
                {
                    FILE *f = fopen(ws.lock_file, "r");
                    if (!f)
                        return false;

                    pid_t old_pid = 0;
                    fscanf(f, "%d", &old_pid);
                    fclose(f);

                    if (old_pid > 0 && kill(old_pid, 0) == 0)
                        return false;

                    unlink(ws.lock_file);

                    fd = open(ws.lock_file,
                              O_CREAT | O_EXCL | O_RDWR,
                              0600);

                    if (fd < 0)
                        return false;
                }
                else
                    return false;
            }

            dprintf(fd, "%d\n", getpid());
            close(fd);

            g_session_registry[i].ws = ws;
            g_session_registry[i].owner_pid = (uint32_t)getpid();
            g_session_registry[i].session_id = (uint32_t)i;

            *out = &g_session_registry[i];
            return true;
        }
    }

    return false;
}

void yai_session_release(yai_session_t *s)
{
    if (!s)
        return;

    unlink(s->ws.lock_file);
    memset(s, 0, sizeof(*s));
}

/* Session dispatch entrypoint. */

void yai_session_dispatch(
    int client_fd,
    const yai_rpc_envelope_t *env,
    const char *payload)
{
    (void)payload;

    if (!env)
        return;

    if (env->ws_id[0] == '\0' || strlen(env->ws_id) == 0) {
        if (env->command_id == YAI_CMD_CONTROL_CALL) {
            yai_session_send_exec_reply(
                client_fd,
                env,
                "error",
                "BAD_ARGS",
                "ws_required",
                "yai.runtime.unknown",
                "runtime",
                NULL);
        } else {
            yai_session_send_binary_response(
                client_fd,
                env,
                env->command_id,
                "{\"status\":\"error\",\"reason\":\"ws_required\"}");
        }
        return;
    }

    yai_session_t *s = NULL;

    if (!yai_session_acquire(&s, env->ws_id))
    {
        if (env->command_id == YAI_CMD_CONTROL_CALL) {
            yai_session_send_exec_reply(
                client_fd,
                env,
                "error",
                "RUNTIME_NOT_READY",
                "session_denied",
                "yai.runtime.unknown",
                "runtime",
                NULL);
        } else {
            yai_session_send_binary_response(
                client_fd,
                env,
                env->command_id,
                "{\"status\":\"error\",\"reason\":\"session_denied\"}");
        }
        return;
    }

    switch (env->command_id)
    {
    case YAI_CMD_PING:
        yai_session_send_binary_response(
            client_fd,
            env,
            YAI_CMD_PING,
            "{\"status\":\"pong\"}");
        goto cleanup;

    case YAI_CMD_CONTROL_CALL:
        (void)yai_session_handle_control_call(client_fd, env, payload, s);
        goto cleanup;

    default:
        yai_session_send_binary_response(
            client_fd,
            env,
            env->command_id,
            "{\"status\":\"nyi\",\"code\":\"NOT_IMPLEMENTED\",\"reason\":\"nyi_deterministic\"}");
        goto cleanup;
    }

cleanup:
    yai_session_release(s);
}

int yai_session_handle_control_call(
    int client_fd,
    const yai_rpc_envelope_t *env,
    const char *payload,
    const yai_session_t *s)
{
    yai_law_resolution_output_t law_out;
    char data[2048];
    char err[256];
    const char *status = "ok";
    const char *code = "OK";
    const char *reason = "accepted";
    const char *effect_name = "unknown";

    if (!env || !s)
        return -1;

    if (!payload || !payload[0])
    {
        yai_session_send_exec_reply(
            client_fd,
            env,
            "error",
            "BAD_ARGS",
            "payload_required",
            "yai.runtime.control_call",
            "runtime",
            NULL);
        return -1;
    }

    memset(&law_out, 0, sizeof(law_out));
    memset(err, 0, sizeof(err));

    if (yai_law_resolve_control_call(s->ws.ws_id,
                                     payload,
                                     env->trace_id,
                                     &law_out,
                                     err,
                                     sizeof(err)) != 0)
    {
        yai_session_send_exec_reply(
            client_fd,
            env,
            "error",
            "INTERNAL_ERROR",
            (err[0] ? err : "law_resolution_failed"),
            "yai.runtime.control_call",
            "runtime",
            NULL);
        return -1;
    }

    effect_name = yai_law_effect_name(law_out.decision.final_effect);

    if (law_out.decision.final_effect == YAI_LAW_EFFECT_DENY ||
        law_out.decision.final_effect == YAI_LAW_EFFECT_QUARANTINE)
    {
        status = "error";
        code = "POLICY_BLOCK";
        reason = effect_name;
    }
    else if (law_out.decision.final_effect == YAI_LAW_EFFECT_REVIEW_REQUIRED)
    {
        status = "ok";
        code = "REVIEW_REQUIRED";
        reason = effect_name;
    }

    if (snprintf(data,
                 sizeof(data),
                 "{"
                 "\"ws_id\":\"%s\","
                 "\"session_id\":%u,"
                 "\"decision\":{"
                   "\"decision_id\":\"%s\","
                   "\"domain_id\":\"%s\","
                   "\"effect\":\"%s\","
                   "\"rationale\":\"%s\""
                 "},"
                 "\"evidence\":{"
                   "\"trace_id\":\"%s\","
                   "\"decision_id\":\"%s\","
                   "\"domain_id\":\"%s\","
                   "\"final_effect\":\"%s\","
                   "\"provider\":\"%s\","
                   "\"resource\":\"%s\","
                   "\"authority_context\":\"%s\""
                 "},"
                 "\"resolution_trace\":%s"
                 "}",
                 s->ws.ws_id,
                 s->session_id,
                 law_out.decision.decision_id,
                 law_out.decision.domain_id,
                 effect_name,
                 law_out.decision.rationale,
                 law_out.evidence.trace_id,
                 law_out.evidence.decision_id,
                 law_out.evidence.domain_id,
                 law_out.evidence.final_effect,
                 law_out.evidence.provider,
                 law_out.evidence.resource,
                 law_out.evidence.authority_context,
                 law_out.trace_json[0] ? law_out.trace_json : "{}") <= 0)
    {
        yai_session_send_exec_reply(
            client_fd,
            env,
            "error",
            "INTERNAL_ERROR",
            "response_encode_failed",
            "yai.runtime.control_call",
            "runtime",
            NULL);
        return -1;
    }

    yai_session_send_exec_reply(
        client_fd,
        env,
        status,
        code,
        reason,
        "yai.runtime.control_call",
        "runtime",
        data);
    return 0;
}
