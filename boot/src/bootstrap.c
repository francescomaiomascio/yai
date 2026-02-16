#define _POSIX_C_SOURCE 200809L

#include "bootstrap.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/wait.h>

#define SYSTEM_WS "system"
#define SHM_VAULT_PREFIX "/yai_vault_"

#define YAI_BIN_DIR "./dist/bin"
#define ROOT_BIN    "yai-root-server"
#define KERNEL_BIN  "yai-kernel"

static int spawn_process(const char *bin_path)
{
    pid_t pid = fork();
    if (pid < 0)
        return -1;

    if (pid == 0) {
        execl(bin_path, bin_path, "--master", NULL);
        perror("[BOOT-FATAL] exec failed");
        _exit(1);
    }

    return pid;
}

/* ============================================================
   VAULT POPULATE
   ============================================================ */

void yai_vault_populate(
    yai_vault_t *vault,
    const char *ws_id,
    uint32_t quota)
{
    memset(vault, 0, sizeof(yai_vault_t));

    vault->status = YAI_STATE_PREBOOT;
    vault->authority_lock = false;
    vault->energy_quota = quota;
    vault->energy_consumed = 0;
    vault->trace_id[0] = '\0';
    vault->logical_clock = 0;

    strncpy(vault->workspace_id, ws_id, MAX_WS_ID - 1);

    printf("[BOOT] Vault populated for WS: %s\n", ws_id);
}

/* ============================================================
   SYSTEM SHM
   ============================================================ */

int yai_init_system_shm(void)
{
    char shm_path[128];

    snprintf(shm_path, sizeof(shm_path),
             "%s%s", SHM_VAULT_PREFIX, SYSTEM_WS);

    shm_unlink(shm_path);

    int fd = shm_open(shm_path, O_CREAT | O_RDWR, 0666);
    if (fd == -1)
        return -1;

    if (ftruncate(fd, sizeof(yai_vault_t)) != 0) {
        close(fd);
        return -2;
    }

    yai_vault_t *v = mmap(NULL,
                          sizeof(yai_vault_t),
                          PROT_READ | PROT_WRITE,
                          MAP_SHARED,
                          fd,
                          0);

    if (v == MAP_FAILED) {
        close(fd);
        return -3;
    }

    memset(v, 0, sizeof(yai_vault_t));
    v->status = YAI_STATE_PREBOOT;
    strncpy(v->workspace_id, SYSTEM_WS, MAX_WS_ID - 1);

    munmap(v, sizeof(yai_vault_t));
    close(fd);

    printf("[BOOT] System SHM initialized (%s)\n", shm_path);

    return 0;
}

/* ============================================================
   MACHINE STARTUP
   ============================================================ */

int yai_boot_master(void)
{
    printf("\n=== YAI MACHINE ENTRYPOINT (L0) ===\n");

    printf("[DISCOVERY] Mapping workspace: %s\n", SYSTEM_WS);

    if (yai_init_system_shm() != 0) {
        printf("[BOOT-FATAL] System SHM init failed\n");
        return -1;
    }

    printf("[BOOT] Environment verified. Launching Root Control Plane...\n");

    char root_path[PATH_MAX];
    char kernel_path[PATH_MAX];

    snprintf(root_path, sizeof(root_path),
             "%s/%s", YAI_BIN_DIR, ROOT_BIN);

    snprintf(kernel_path, sizeof(kernel_path),
             "%s/%s", YAI_BIN_DIR, KERNEL_BIN);

    if (access(root_path, X_OK) != 0) {
        printf("[BOOT-FATAL] Root binary missing: %s\n", root_path);
        return -2;
    }

    if (access(kernel_path, X_OK) != 0) {
        printf("[BOOT-FATAL] Kernel binary missing: %s\n", kernel_path);
        return -3;
    }

    int root_pid = spawn_process(root_path);
    if (root_pid < 0) {
        printf("[BOOT-FATAL] Root spawn failed\n");
        return -4;
    }

    int kernel_pid = spawn_process(kernel_path);
    if (kernel_pid < 0) {
        printf("[BOOT-FATAL] Kernel spawn failed\n");
        return -5;
    }

    printf("[BOOT] Root (%d) and Kernel (%d) launched successfully\n",
           root_pid, kernel_pid);

    printf("[BOOT] Boot completed. Machine runtime is UP.\n");

    return 0;
}
