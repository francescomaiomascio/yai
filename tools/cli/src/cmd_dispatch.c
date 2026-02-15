// tools/cli/src/cmd_dispatch.c

#include "../include/yai_cmd.h"
#include "../include/yai_fmt.h"

#include <stdio.h>
#include <string.h>

/*
 * Central Sovereign Dispatcher
 *
 * Routing rules:
 *  - root   → L1 machine plane
 *  - kernel → L1 machine plane (global control)
 *  - engine → L2 (requires --ws)
 *  - mind   → L3 (requires --ws)
 *  - law    → local
 */

static void usage_global(void)
{
    fprintf(stderr,
        "YAI Sovereign CLI\n"
        "\nUsage:\n"
        "  yai root   <status|ping>\n"
        "  yai kernel <status|ping|stop|ws>\n"
        "  yai engine --ws <id> <gate> <method> [params]\n"
        "  yai mind   --ws <id> <chat|think|query> <prompt>\n"
        "  yai law    <check|tree|status>\n"
    );
}

int yai_cmd_dispatch(
    const char *binary,
    int argc,
    char **argv,
    const yai_cli_opts_t *opt
)
{
    if (!binary || !binary[0]) {
        usage_global();
        return 2;
    }

    /* ---------------- ROOT ---------------- */

    if (strcmp(binary, "root") == 0)
        return yai_cmd_root(argc, argv, opt);

    /* ---------------- KERNEL ---------------- */

    if (strcmp(binary, "kernel") == 0) {
        if (argc > 0 && strcmp(argv[0], "ws") == 0)
            return yai_cmd_ws(argc - 1, argv + 1, opt);

        return yai_cmd_kernel(argc, argv, opt);
    }

    /* ---------------- ENGINE ---------------- */

    if (strcmp(binary, "engine") == 0) {
        if (!opt || !opt->ws_id || !opt->ws_id[0]) {
            fprintf(stderr,
                "FATAL: 'engine' requires --ws <id>\n");
            return 3;
        }
        return yai_cmd_engine(argc, argv, opt);
    }

    /* ---------------- MIND ---------------- */

    if (strcmp(binary, "mind") == 0) {
        if (!opt || !opt->ws_id || !opt->ws_id[0]) {
            fprintf(stderr,
                "FATAL: 'mind' requires --ws <id>\n");
            return 3;
        }
        return yai_cmd_mind(argc, argv, opt);
    }

    /* ---------------- LAW ---------------- */

    if (strcmp(binary, "law") == 0)
        return yai_cmd_law(argc, argv, opt);

    /* ---------------- UNKNOWN ---------------- */

    fprintf(stderr, "ERR: Unknown target: %s\n", binary);
    usage_global();
    return 2;
}
