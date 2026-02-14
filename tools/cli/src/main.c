#include "../include/yai_cli.h"
#include "../include/yai_cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_usage() {
    printf("YAI Sovereign CLI\n");
    printf("Usage: yai <bin> [options] <command> [args...]\n\n");
    printf("Binaries (Levels):\n");
    printf("  kernel   L1: Root control, session management, power\n");
    printf("  engine   L2: Storage gates, providers, resources\n");
    printf("  mind     L3: Cognition, RAG, Agents (Requires --ws)\n");
    printf("\nOptions:\n");
    printf("  -w, --ws <id>   Target workspace (Required for 'mind')\n");
    printf("  -j, --json      Raw JSON output\n");
    printf("  -a, --arming    Enable destructive/system commands\n");
}

static int is_flag(const char *a, const char *s, const char *l) {
    return (a && ((s && strcmp(a, s) == 0) || (l && strcmp(a, l) == 0)));
}

int main(int argc, char **argv) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    yai_cli_opts_t opt;
    memset(&opt, 0, sizeof(opt));
    opt.role = "user";
    opt.client_version = "yai-cli/v1-adr-compliant";

    // Identifica il binario logico (kernel, engine, mind)
    const char *target_bin = argv[1];
    
    // Default workspace dall'ambiente
    const char* env_ws = getenv("YAI_WORKSPACE");
    opt.ws_id = env_ws;

    int i = 2; // Inizia il parsing dopo <bin>
    for (; i < argc; i++) {
        const char *a = argv[i];
        if (a[0] != '-') break; // Fine flag, inizio comando

        if (is_flag(a, "-w", "--ws")) {
            if (++i >= argc) { fprintf(stderr, "ERR: --ws needs value\n"); return 2; }
            opt.ws_id = argv[i];
        } else if (is_flag(a, "-j", "--json")) {
            opt.json = 1;
        } else if (is_flag(a, "-a", "--arming")) {
            opt.arming = 1;
        } else if (is_flag(a, "-r", "--role")) {
            if (++i >= argc) { fprintf(stderr, "ERR: --role needs value\n"); return 2; }
            opt.role = argv[i];
        }
    }

    // --- Validazione Rigida ADR-001 ---
    if (strcmp(target_bin, "mind") == 0) {
        if (!opt.ws_id || strlen(opt.ws_id) == 0) {
            fprintf(stderr, "FATAL: 'mind' requires a workspace. Use --ws or YAI_WORKSPACE env.\n");
            return 3;
        }
    }

    if (i >= argc) {
        fprintf(stderr, "ERR: Missing command for binary '%s'.\n", target_bin);
        return 2;
    }

    // Il dispatcher riceve il binario target e il resto degli argomenti
    // Esempio: yai mind --ws dev chat -> dispatch("mind", ["chat"], &opt)
    return yai_cmd_dispatch(target_bin, argc - i, argv + i, &opt);
}