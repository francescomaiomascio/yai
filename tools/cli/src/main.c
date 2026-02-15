// tools/cli/src/main.c

#include "../include/yai_cli.h"
#include "../include/yai_cmd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef YAI_CLI_VERSION
#define YAI_CLI_VERSION "yai-cli/1.0"
#endif

static void print_usage(void) {
    printf("YAI Sovereign CLI\n\n");
    printf("Usage:\n");
    printf("  yai <bin> [options] <command> [args...]\n");
    printf("  yai --help | -h\n");
    printf("  yai --version | -V\n\n");
    printf("Bins (Planes):\n");
    printf("  root     Machine plane (global authority)\n");
    printf("  kernel   L1: Workspaces + runtime control\n");
    printf("  engine   L2: Gates (requires --ws)\n");
    printf("  mind     L3: Cognition (requires --ws)\n");
    printf("  law      Local checks (no RPC)\n\n");
    printf("Options:\n");
    printf("  -w, --ws <id>     Target workspace\n");
    printf("  -j, --json        Raw JSON output\n");
    printf("  -a, --arming      Enable privileged commands\n");
    printf("  -r, --role <...>  Role (default: user)\n\n");
    printf("Examples:\n");
    printf("  yai root status\n");
    printf("  yai kernel ws list\n");
    printf("  yai engine --ws dev storage put_node '{\"id\":\"n1\"}'\n");
    printf("  yai mind   --ws dev chat \"ciao\"\n");
}

static void print_version(void) {
    printf("%s\n", YAI_CLI_VERSION);
}

static int is_flag(const char *a, const char *s, const char *l) {
    return (a && ((s && strcmp(a, s) == 0) || (l && strcmp(a, l) == 0)));
}

static int is_help(const char *a) {
    return is_flag(a, "-h", "--help") || (a && strcmp(a, "help") == 0);
}

static int is_version(const char *a) {
    return is_flag(a, "-V", "--version") || (a && strcmp(a, "version") == 0);
}

int main(int argc, char **argv) {

    if (argc < 2) {
        print_usage();
        return 1;
    }

    if (is_help(argv[1])) {
        print_usage();
        return 0;
    }

    if (is_version(argv[1])) {
        print_version();
        return 0;
    }

    yai_cli_opts_t opt;
    memset(&opt, 0, sizeof(opt));

    opt.role = "user";
    opt.client_version = YAI_CLI_VERSION;

    const char *env_ws = getenv("YAI_WORKSPACE");
    opt.ws_id = env_ws;

    const char *target_bin = argv[1];
    int i = 2;

    if (i < argc && is_help(argv[i])) {
        return yai_cmd_dispatch(target_bin, 1, (char*[]){"help"}, &opt);
    }

    for (; i < argc; i++) {
        const char *a = argv[i];
        if (!a || a[0] != '-') break;

        if (is_flag(a, "-w", "--ws")) {
            if (++i >= argc) {
                fprintf(stderr, "ERR: --ws requires value\n");
                return 2;
            }
            opt.ws_id = argv[i];

        } else if (is_flag(a, "-j", "--json")) {
            opt.json = 1;

        } else if (is_flag(a, "-a", "--arming")) {
            opt.arming = 1;

        } else if (is_flag(a, "-r", "--role")) {
            if (++i >= argc) {
                fprintf(stderr, "ERR: --role requires value\n");
                return 2;
            }
            opt.role = argv[i];

        } else if (is_flag(a, "-h", "--help")) {
            return yai_cmd_dispatch(target_bin, 1, (char*[]){"help"}, &opt);

        } else {
            fprintf(stderr, "ERR: unknown option: %s\n", a);
            return 2;
        }
    }

    /* ADR enforcement */
    if (strcmp(target_bin, "engine") == 0 ||
        strcmp(target_bin, "mind") == 0) {

        if (!opt.ws_id || !opt.ws_id[0]) {
            fprintf(stderr,
                "FATAL: '%s' requires --ws <id>\n",
                target_bin);
            return 3;
        }
    }

    if (i >= argc) {
        fprintf(stderr,
            "ERR: Missing command for '%s'\n",
            target_bin);
        fprintf(stderr,
            "Try: yai %s --help\n",
            target_bin);
        return 2;
    }

    return yai_cmd_dispatch(
        target_bin,
        argc - i,
        argv + i,
        &opt);
}
