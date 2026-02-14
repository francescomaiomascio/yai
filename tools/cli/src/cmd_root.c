#include "../include/yai_cmd.h"
#include "../include/yai_rpc.h"
#include "../include/yai_fmt.h"
#include "../include/yai_envelope.h"
#include "../include/yai_cmd_law.h" 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void usage(void) {
    fprintf(stderr,
        "YAI SOVEREIGN CLI - Root Dispatcher\n"
        "USAGE:\n"
        "  yai kernel <status|ping|stop|ws>   (L1: System & Tenants)\n"
        "  yai engine <storage|network> <cmd> (L2: Data Gates)\n"
        "  yai mind   <chat|think|query>      (L3: AI & Cognition)\n"
        "  yai law    <check|tree|paths>      (Local Law Enforcement)\n"
        "\nGLOBAL FLAGS:\n"
        "  --ws <id>           Target workspace (Required for L2/L3)\n"
        "  --arming            Enable privileged/destructive commands\n"
        "  --role <user|op>    Access control role (default: user)\n"
        "  --json              Output raw JSON response\n"
    );
}

/**
 * Dispatcher Centrale (ADR-002 Compliant)
 * Separa i comandi locali (law) dai comandi instradati al Root Plane.
 */
int yai_cmd_dispatch(const char *binary, int argc, char **argv, const yai_cli_opts_t *opt) { // <-- AGGIUNTO const
    if (!binary) { usage(); return 2; }

    // 1. GESTIONE COMANDI LOCALI (No RPC)
    // 'law' opera direttamente sul filesystem locale per validare le specifiche.
    if (strcmp(binary, "law") == 0) {
        if (argc < 1) { fprintf(stderr, "ERR: law requires subcommand\n"); return 2; }
        return yai_cmd_law(argc, argv, opt);
    }

    if (strcmp(binary, "help") == 0 || strcmp(binary, "-h") == 0) {
        usage();
        return 0;
    }

    // 2. GESTIONE COMANDI REMOTI (RPC via Root Socket)
    // A questo punto 'binary' deve essere kernel, engine o mind.
    
    // Validazione preventiva: L2 ed L3 richiedono sempre un workspace
    if ((strcmp(binary, "engine") == 0 || strcmp(binary, "mind") == 0)) {
        if (!opt->ws_id || !opt->ws_id[0]) {
            fprintf(stderr, "FATAL: Level '%s' requires --ws <id> for tenant isolation.\n", binary);
            return 2;
        }
    }

    // Connessione al Root Control Plane
    yai_rpc_client_t c;
    int rc = yai_rpc_connect(&c, opt->ws_id);
    if (rc != 0) { 
        fprintf(stderr, "ERR: Connection to Root Plane failed. Is yai-kernel running?\n"); 
        return 3; 
    }

    // Eseguiamo sempre un handshake per validare il protocollo
    const char *ver = opt->client_version ? opt->client_version : "cli-c/1.0";
    rc = yai_rpc_handshake(&c, binary, ver);
    if (rc != 0) { 
        fprintf(stderr, "ERR: Protocol handshake failed.\n"); 
        yai_rpc_close(&c); 
        return 4; 
    }

    // Routing interno in base al binario target
    int final_rc = 1;
    
    if (strcmp(binary, "kernel") == 0) {
        // Se è 'yai kernel ws ...' usiamo il modulo workspace
        if (argc > 0 && strcmp(argv[0], "ws") == 0) {
            final_rc = yai_cmd_ws(argc - 1, argv + 1, opt);
        } else {
            final_rc = yai_cmd_kernel(argc, argv, opt);
        }
    } 
    else if (strcmp(binary, "engine") == 0) {
        final_rc = yai_cmd_engine(argc, argv, opt);
    } 
    else if (strcmp(binary, "mind") == 0) {
        final_rc = yai_cmd_mind(argc, argv, opt);
    } 
    else {
        fprintf(stderr, "ERR: Unknown binary target: %s\n", binary);
        usage();
        final_rc = 2;
    }

    yai_rpc_close(&c);
    return final_rc;
}