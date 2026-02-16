#define _POSIX_C_SOURCE 200809L

#include "preboot.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

static int mkdir_safe(const char *path)
{
    if (mkdir(path, 0700) == 0)
        return 0;

    if (errno == EEXIST)
        return 0;

    return -1;
}

static int ensure_dir(const char *base, const char *sub)
{
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", base, sub);
    return mkdir_safe(path);
}

int yai_ensure_runtime_layout(const char *ws_id)
{
    const char *home = getenv("HOME");
    if (!home)
        return -1;

    char root[1024];
    snprintf(root, sizeof(root), "%s/.yai", home);

    if (mkdir_safe(root) != 0)
        return -2;

    char run[1024];
    snprintf(run, sizeof(run), "%s/.yai/run", home);

    if (mkdir_safe(run) != 0)
        return -3;

    if (ensure_dir(run, ws_id) != 0)
        return -4;

    if (ensure_dir(run, "kernel") != 0)
        return -5;

    if (ensure_dir(run, "logs") != 0)
        return -6;

    return 0;
}

int yai_run_preboot_checks(void)
{
    if (getuid() == 0) {
        printf("[PREBOOT] Warning: Running as root is not YAI-compliant\n");
    }

    return 0;
}

void yai_discover_environment(yai_vault_t *vault)
{
    printf("[DISCOVERY] Mapping workspace: %s\n",
           vault->workspace_id);

    if (yai_ensure_runtime_layout(vault->workspace_id) == 0)
        printf("[DISCOVERY] Runtime directory ready for %s\n",
               vault->workspace_id);
    else
        printf("[DISCOVERY-WARN] Runtime layout incomplete\n");

    snprintf(vault->trace_id,
             MAX_TRACE_ID,
             "boot-%08x",
             0xDEADC0DE);
}
