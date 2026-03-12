/* SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include <yai/sdk/context.h>
#include <yai/sdk/client.h>
#include <yai/sdk/errors.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Canonical workspace command ids for workspace-bound runtime interaction. */
#define YAI_SDK_CMD_WORKSPACE_CREATE "yai.workspace.create"
#define YAI_SDK_CMD_WORKSPACE_OPEN "yai.workspace.open"
#define YAI_SDK_CMD_WORKSPACE_SET "yai.workspace.set"
#define YAI_SDK_CMD_WORKSPACE_SWITCH "yai.workspace.switch"
#define YAI_SDK_CMD_WORKSPACE_CURRENT "yai.workspace.current"
#define YAI_SDK_CMD_WORKSPACE_UNSET "yai.workspace.unset"
#define YAI_SDK_CMD_WORKSPACE_CLEAR "yai.workspace.clear"
#define YAI_SDK_CMD_WORKSPACE_RESET "yai.workspace.reset"
#define YAI_SDK_CMD_WORKSPACE_DESTROY "yai.workspace.destroy"
#define YAI_SDK_CMD_WORKSPACE_STATUS "yai.workspace.status"
#define YAI_SDK_CMD_WORKSPACE_INSPECT "yai.workspace.inspect"
#define YAI_SDK_CMD_WORKSPACE_QUERY "yai.workspace.query"
#define YAI_SDK_CMD_WORKSPACE_GRAPH_SUMMARY "yai.workspace.graph.summary"
#define YAI_SDK_CMD_WORKSPACE_GRAPH_WORKSPACE "yai.workspace.graph.workspace"
#define YAI_SDK_CMD_WORKSPACE_GRAPH_GOVERNANCE "yai.workspace.graph.governance"
#define YAI_SDK_CMD_WORKSPACE_GRAPH_DECISION "yai.workspace.graph.decision"
#define YAI_SDK_CMD_WORKSPACE_GRAPH_EVIDENCE "yai.workspace.graph.evidence"
#define YAI_SDK_CMD_WORKSPACE_GRAPH_AUTHORITY "yai.workspace.graph.authority"
#define YAI_SDK_CMD_WORKSPACE_GRAPH_ARTIFACT "yai.workspace.graph.artifact"
#define YAI_SDK_CMD_WORKSPACE_GRAPH_LINEAGE "yai.workspace.graph.lineage"
#define YAI_SDK_CMD_WORKSPACE_GRAPH_RECENT "yai.workspace.graph.recent"
#define YAI_SDK_CMD_WORKSPACE_RUN "yai.workspace.run"
#define YAI_SDK_CMD_WORKSPACE_EVENTS_TAIL "yai.workspace.events.tail"
#define YAI_SDK_CMD_WORKSPACE_POLICY_EFFECTIVE "yai.workspace.policy_effective"
#define YAI_SDK_CMD_WORKSPACE_POLICY_DRY_RUN "yai.workspace.policy_dry_run"
#define YAI_SDK_CMD_WORKSPACE_POLICY_ATTACH "yai.workspace.policy_attach"
#define YAI_SDK_CMD_WORKSPACE_POLICY_ACTIVATE "yai.workspace.policy_activate"
#define YAI_SDK_CMD_WORKSPACE_POLICY_DETACH "yai.workspace.policy_detach"
#define YAI_SDK_CMD_WORKSPACE_DOMAIN_GET "yai.workspace.domain_get"
#define YAI_SDK_CMD_WORKSPACE_DOMAIN_SET "yai.workspace.domain_set"
#define YAI_SDK_CMD_WORKSPACE_DEBUG_RESOLUTION "yai.workspace.debug_resolution"
#define YAI_SDK_CMD_WORKSPACE_RECOVERY_STATUS "yai.workspace.status"
#define YAI_SDK_CMD_WORKSPACE_RECOVERY_LOAD "yai.workspace.lifecycle.maintain"
#define YAI_SDK_CMD_WORKSPACE_RECOVERY_REOPEN "yai.workspace.open"
#define YAI_SDK_CMD_SOURCE_ENROLL "yai.source.enroll"
#define YAI_SDK_CMD_SOURCE_ATTACH "yai.source.attach"
#define YAI_SDK_CMD_SOURCE_EMIT "yai.source.emit"
#define YAI_SDK_CMD_SOURCE_STATUS "yai.source.status"

/* Workspace query families surfaced by canonical typed helpers. */
#define YAI_SDK_WS_QUERY_FAMILY_WORKSPACE "workspace"
#define YAI_SDK_WS_QUERY_FAMILY_EVENTS "events"
#define YAI_SDK_WS_QUERY_FAMILY_EVIDENCE "evidence"
#define YAI_SDK_WS_QUERY_FAMILY_GOVERNANCE "governance"
#define YAI_SDK_WS_QUERY_FAMILY_AUTHORITY "authority"
#define YAI_SDK_WS_QUERY_FAMILY_ARTIFACT "artifact"
#define YAI_SDK_WS_QUERY_FAMILY_ENFORCEMENT "enforcement"
#define YAI_SDK_WS_QUERY_FAMILY_TRANSIENT "transient"
#define YAI_SDK_WS_QUERY_FAMILY_MEMORY "memory"
#define YAI_SDK_WS_QUERY_FAMILY_PROVIDERS "providers"
#define YAI_SDK_WS_QUERY_FAMILY_CONTEXT "context"
#define YAI_SDK_WS_QUERY_FAMILY_SOURCE "source"

static inline int yai_sdk_workspace_command(
    yai_sdk_client_t *client,
    const char *command_id,
    size_t argv_len,
    const char *const *argv,
    yai_sdk_reply_t *out)
{
    yai_sdk_control_call_t call = {
        .target_plane = "runtime",
        .command_id = command_id,
        .argv = argv,
        .argv_len = argv_len,
    };
    return yai_sdk_client_call(client, &call, out);
}

static inline int yai_sdk_workspace_command0(
    yai_sdk_client_t *client,
    const char *command_id,
    yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command(client, command_id, 0, NULL, out);
}

static inline int yai_sdk_workspace_command1(
    yai_sdk_client_t *client,
    const char *command_id,
    const char *arg0,
    yai_sdk_reply_t *out)
{
    const char *argv[1] = {arg0};
    return yai_sdk_workspace_command(client, command_id, 1, argv, out);
}

/* Canonical workspace-first runtime helpers (lifecycle/binding). */
static inline int yai_sdk_ws_create(yai_sdk_client_t *client, const char *ws_id, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command1(client, YAI_SDK_CMD_WORKSPACE_CREATE, ws_id, out);
}

static inline int yai_sdk_ws_open(yai_sdk_client_t *client, const char *ws_id, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command1(client, YAI_SDK_CMD_WORKSPACE_OPEN, ws_id, out);
}

static inline int yai_sdk_ws_set(yai_sdk_client_t *client, const char *ws_id, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command1(client, YAI_SDK_CMD_WORKSPACE_SET, ws_id, out);
}

static inline int yai_sdk_ws_switch(yai_sdk_client_t *client, const char *ws_id, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command1(client, YAI_SDK_CMD_WORKSPACE_SWITCH, ws_id, out);
}

static inline int yai_sdk_ws_current(yai_sdk_client_t *client, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command0(client, YAI_SDK_CMD_WORKSPACE_CURRENT, out);
}

static inline int yai_sdk_ws_status(yai_sdk_client_t *client, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command0(client, YAI_SDK_CMD_WORKSPACE_STATUS, out);
}

static inline int yai_sdk_ws_inspect(yai_sdk_client_t *client, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command0(client, YAI_SDK_CMD_WORKSPACE_INSPECT, out);
}

static inline int yai_sdk_ws_unset(yai_sdk_client_t *client, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command0(client, YAI_SDK_CMD_WORKSPACE_UNSET, out);
}

static inline int yai_sdk_ws_clear(yai_sdk_client_t *client, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command0(client, YAI_SDK_CMD_WORKSPACE_CLEAR, out);
}

static inline int yai_sdk_ws_reset(yai_sdk_client_t *client, const char *ws_id, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command1(client, YAI_SDK_CMD_WORKSPACE_RESET, ws_id, out);
}

static inline int yai_sdk_ws_destroy(yai_sdk_client_t *client, const char *ws_id, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command1(client, YAI_SDK_CMD_WORKSPACE_DESTROY, ws_id, out);
}

/* Generic query fallback stays available by design. */
static inline int yai_sdk_ws_query_family(
    yai_sdk_client_t *client,
    const char *query_family,
    yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command1(client, YAI_SDK_CMD_WORKSPACE_QUERY, query_family, out);
}

/* Domain helpers. */
static inline int yai_sdk_ws_domain_get(yai_sdk_client_t *client, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command0(client, YAI_SDK_CMD_WORKSPACE_DOMAIN_GET, out);
}

static inline int yai_sdk_ws_domain_set(
    yai_sdk_client_t *client,
    const char *family,
    const char *specialization,
    yai_sdk_reply_t *out)
{
    if (!family || !family[0] || !specialization || !specialization[0]) {
        return YAI_SDK_BAD_ARGS;
    }
    const char *argv[4] = {"--family", family, "--specialization", specialization};
    return yai_sdk_workspace_command(client, YAI_SDK_CMD_WORKSPACE_DOMAIN_SET, 4, argv, out);
}

/* Policy/governance helpers. */
static inline int yai_sdk_ws_policy_attach(
    yai_sdk_client_t *client,
    const char *object_id,
    yai_sdk_reply_t *out)
{
    if (!object_id || !object_id[0]) {
        return YAI_SDK_BAD_ARGS;
    }
    return yai_sdk_workspace_command1(client, YAI_SDK_CMD_WORKSPACE_POLICY_ATTACH, object_id, out);
}

static inline int yai_sdk_ws_policy_detach(
    yai_sdk_client_t *client,
    const char *object_id,
    yai_sdk_reply_t *out)
{
    if (!object_id || !object_id[0]) {
        return YAI_SDK_BAD_ARGS;
    }
    return yai_sdk_workspace_command1(client, YAI_SDK_CMD_WORKSPACE_POLICY_DETACH, object_id, out);
}

static inline int yai_sdk_ws_policy_activate(
    yai_sdk_client_t *client,
    const char *object_id,
    yai_sdk_reply_t *out)
{
    if (!object_id || !object_id[0]) {
        return YAI_SDK_BAD_ARGS;
    }
    return yai_sdk_workspace_command1(client, YAI_SDK_CMD_WORKSPACE_POLICY_ACTIVATE, object_id, out);
}

static inline int yai_sdk_ws_policy_dry_run(
    yai_sdk_client_t *client,
    const char *object_id,
    yai_sdk_reply_t *out)
{
    if (!object_id || !object_id[0]) {
        return YAI_SDK_BAD_ARGS;
    }
    return yai_sdk_workspace_command1(client, YAI_SDK_CMD_WORKSPACE_POLICY_DRY_RUN, object_id, out);
}

static inline int yai_sdk_ws_policy_effective(yai_sdk_client_t *client, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command0(client, YAI_SDK_CMD_WORKSPACE_POLICY_EFFECTIVE, out);
}

/* Recovery/debug helpers. */
static inline int yai_sdk_ws_recovery_status(yai_sdk_client_t *client, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command0(client, YAI_SDK_CMD_WORKSPACE_RECOVERY_STATUS, out);
}

static inline int yai_sdk_ws_recovery_load(yai_sdk_client_t *client, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command0(client, YAI_SDK_CMD_WORKSPACE_RECOVERY_LOAD, out);
}

static inline int yai_sdk_ws_recovery_reopen(
    yai_sdk_client_t *client,
    const char *ws_id,
    yai_sdk_reply_t *out)
{
    if (!ws_id || !ws_id[0]) {
        return YAI_SDK_BAD_ARGS;
    }
    return yai_sdk_workspace_command1(client, YAI_SDK_CMD_WORKSPACE_RECOVERY_REOPEN, ws_id, out);
}

static inline int yai_sdk_ws_debug_resolution(yai_sdk_client_t *client, yai_sdk_reply_t *out)
{
    return yai_sdk_workspace_command0(client, YAI_SDK_CMD_WORKSPACE_DEBUG_RESOLUTION, out);
}

/* Canonical workspace-binding API aliases. */
static inline int yai_sdk_workspace_bind(const char *ws_id)
{
    return yai_sdk_context_set_current_workspace(ws_id);
}

static inline int yai_sdk_workspace_switch(const char *ws_id)
{
    return yai_sdk_context_switch_workspace(ws_id);
}

static inline int yai_sdk_workspace_unbind(void)
{
    return yai_sdk_context_unset_workspace();
}

static inline int yai_sdk_workspace_clear_binding(void)
{
    return yai_sdk_context_clear_current_workspace();
}

static inline int yai_sdk_workspace_current(char *out_ws_id, size_t out_cap)
{
    return yai_sdk_context_get_current_workspace(out_ws_id, out_cap);
}

static inline int yai_sdk_workspace_resolve(
    const char *explicit_ws_id,
    char *out_ws_id,
    size_t out_cap)
{
    return yai_sdk_context_resolve_workspace(explicit_ws_id, out_ws_id, out_cap);
}

/* Runtime-backed workspace status helper (thin alias). */
static inline int yai_sdk_workspace_status(
    const char *ws_id,
    yai_sdk_workspace_info_t *out)
{
    return yai_sdk_workspace_describe(ws_id, out);
}

static inline int yai_sdk_workspace_validate_binding(yai_sdk_workspace_info_t *out)
{
    return yai_sdk_context_validate_current_workspace(out);
}

#ifdef __cplusplus
}
#endif
