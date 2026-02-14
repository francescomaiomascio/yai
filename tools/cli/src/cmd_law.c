#include "../include/yai_cmd_law.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

static int file_exists(const char *p) {
    struct stat st;
    return (p && p[0] && stat(p, &st) == 0 && S_ISREG(st.st_mode));
}

static int dir_exists(const char *p) {
    struct stat st;
    return (p && p[0] && stat(p, &st) == 0 && S_ISDIR(st.st_mode));
}

/**
 * Cerca di capire dove si trova la root 'law/'.
 * Se siamo in tools/cli/, dobbiamo risalire di due livelli.
 */
static const char* find_law_prefix() {
    if (dir_exists("law")) return "";
    if (dir_exists("../../law")) return "../../";
    if (dir_exists("../law")) return "../";
    return NULL;
}

static const char *REQ_FILES[] = {
    "law/specs/control/control_plane.v1.json",
    "law/specs/control/authority.json",
    "law/specs/protocol/protocol.h",
    "law/specs/protocol/yai_protocol_ids.h", 
    "law/formal/YAI_KERNEL.tla",
    "law/formal/spec_map.md",
    NULL
};

static void law_usage(void) {
    printf("YAI Sovereign Law Enforcement\n");
    printf("Usage: yai law <check|tree|status>\n");
}

static int cmd_check(void) {
    const char *prefix = find_law_prefix();
    if (!prefix) {
        fprintf(stderr, "[law][FATAL] Could not locate 'law/' directory. Are you inside the YAI repository?\n");
        return 2;
    }

    int ok = 1;
    printf("[law] Validating Integrity (Prefix: '%s')\n", prefix[0] ? prefix : "./");

    for (int i = 0; REQ_FILES[i] != NULL; i++) {
        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s%s", prefix, REQ_FILES[i]);

        if (file_exists(full_path)) {
            printf("  [OK]   %-40s\n", REQ_FILES[i]);
        } else {
            fprintf(stderr, "  [FAIL] %-40s (NOT FOUND)\n", REQ_FILES[i]);
            ok = 0;
        }
    }

    if (ok) {
        printf("\n[law] Status: PROVISIONS_MET (System is Sovereign)\n");
        return 0;
    } else {
        fprintf(stderr, "\n[law] Status: VIOLATION_DETECTED (Missing Core Specifications)\n");
        return 2;
    }
}

static int cmd_tree(void) {
    // Rappresentazione logica della gerarchia ADR
    puts("law/ (The Sovereignty Root)");
    puts("├── axioms/      # Fundamental truths");
    puts("├── boundaries/  # L0-Lx Isolation rules");
    puts("├── formal/      # TLA+ Specifications");
    puts("└── specs/       # Machine-readable JSON/H laws");
    puts("    ├── control/ # Root Plane Authority");
    puts("    └── protocol/# RPC & Wire format");
    return 0;
}

int yai_cmd_law(int argc, char **argv, const yai_cli_opts_t *opt) {
    (void)opt;
    if (argc < 1) { law_usage(); return 1; }

    const char *sub = argv[0];
    if (strcmp(sub, "check") == 0) return cmd_check();
    if (strcmp(sub, "tree")  == 0) return cmd_tree();
    if (strcmp(sub, "status") == 0) {
        return (find_law_prefix() != NULL) ? 0 : 1;
    }

    law_usage();
    return 1;
}