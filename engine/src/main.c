#include "../include/engine_bridge.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void handle_panic(int sig) {
    printf("\n[YAI-C] Signal %d: Emergency Lock.\n", sig);
    IceVault* v = yai_get_vault();
    {
        char addr_buf[32];
        snprintf(addr_buf, sizeof(addr_buf), "%p", (void*)v);
        setenv("YAI_VAULT_ADDR", addr_buf, 1);
    }
    if (v) {
        v->status = YAI_STATE_ERROR;
        v->authority_lock = true;
    }
    exit(sig);
}

typedef struct {
    IceVault* core;
    IceVault* stream;
    IceVault* brain;
    IceVault* audit;
    IceVault* cache;
    IceVault* control;
} IceVaultCluster;

static void validate_vault_integrity(IceVaultCluster *c) {
    if (!c || !c->core || !c->brain) return;
    if (c->core->energy_consumed > c->core->energy_quota) {
        printf("[SECURITY] Energy Quota Exceeded. Throttling Brain...\n");
        c->brain->authority_lock = true;
    }
}

static void process_command(IceVault* v) {
    if (!v) return;

    v->last_result = 0;
    v->response_buffer[0] = '\0';

    uint32_t cmd_class = yai_command_class_for((yai_command_id_t)v->last_command_id);
    if (cmd_class & YAI_CMD_CLASS_EXTERNAL) {
        if (v->authority_lock) {
            snprintf(v->last_error, sizeof(v->last_error), "External effect denied: authority required");
            v->last_result = 0;
            v->status = YAI_STATE_SUSPENDED;
            return;
        }
        // Minimum external-effect evidence (I-006)
        snprintf(
            v->response_buffer,
            sizeof(v->response_buffer),
            "effect=external;class=%s;target=unspecified;irreversible=%s;authority=ok;intent=unspecified;risk=unspecified;mitigation=none",
            (cmd_class & YAI_CMD_CLASS_IRREVERSIBLE) ? "irreversible" : "external",
            (cmd_class & YAI_CMD_CLASS_IRREVERSIBLE) ? "true" : "false"
        );
    }

    v->status = YAI_STATE_RUNNING;
    switch (v->last_command_id) {
        case YAI_CMD_PING:
            snprintf(v->response_buffer, sizeof(v->response_buffer), "PONG");
            v->last_result = 1;
            v->status = YAI_STATE_READY;
            break;
        case YAI_CMD_NOOP:
            snprintf(v->response_buffer, sizeof(v->response_buffer), "OK");
            v->last_result = 1;
            v->status = YAI_STATE_READY;
            break;
        case YAI_CMD_RECONFIGURE:
            if (v->status != YAI_STATE_SUSPENDED) {
                snprintf(v->last_error, sizeof(v->last_error), "Reconfigure requires SUSPENDED state");
                v->last_result = 0;
                v->status = YAI_STATE_SUSPENDED;
                break;
            }
            // Clear authority lock (cognitive_map -> TRUE) and reset to HALT
            v->authority_lock = false;
            v->status = YAI_STATE_HALT;
            snprintf(v->response_buffer, sizeof(v->response_buffer), "RECONFIGURED");
            v->last_result = 1;
            break;
        default:
            snprintf(v->last_error, sizeof(v->last_error), "Unknown command id: %u", v->last_command_id);
            v->last_result = 0;
            v->status = YAI_STATE_ERROR;
            break;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: ./yai-engine <workspace_id>\n");
        return 1;
    }

    signal(SIGINT, handle_panic);
    signal(SIGTERM, handle_panic);

    IceVaultCluster cluster;
    cluster.core = yai_bridge_attach(argv[1], "");
    cluster.stream = yai_bridge_attach(argv[1], "stream");
    cluster.brain = yai_bridge_attach(argv[1], "brain");
    cluster.audit = yai_bridge_attach(argv[1], "audit");
    cluster.cache = yai_bridge_attach(argv[1], "cache");
    cluster.control = yai_bridge_attach(argv[1], "control");

    if (!cluster.core || !cluster.stream || !cluster.brain || !cluster.audit || !cluster.cache || !cluster.control) {
        fprintf(stderr, "FATAL: Multi-Vault RAID attach failed.\n");
        return 1;
    }

    IceVault* v = cluster.core;
    printf("[YAI-C] Engine Running for WS: %s\n", argv[1]);
    v->status = YAI_STATE_READY;
    v->last_processed_seq = 0;
    uint32_t last_seen_seq = v->last_processed_seq;
    while (v->status != YAI_STATE_ERROR && v->status != YAI_STATE_HALT) {
        validate_vault_integrity(&cluster);
        if (v->command_seq != last_seen_seq) {
            last_seen_seq = v->command_seq;
            process_command(v);
            v->last_processed_seq = last_seen_seq;
        }
        usleep(50000);
    }

    yai_bridge_detach();
    return 0;
} // <--- CONTROLLA CHE QUESTA CI SIA!
