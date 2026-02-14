#define _POSIX_C_SOURCE 200809L
#include "yai_vault.h"
#include "preboot.h"
#include "bootstrap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <libgen.h>

#define KERNEL_BINARY "yai-kernel"
#define SYSTEM_WS "system" // Il Bootstrap opera solo sul piano di sistema

static const char *resolve_kernel_path(char **argv) {
    const char *env = getenv("YAI_KERNEL_BIN");
    if (env && env[0] != '\0') return env;

    static char buf[PATH_MAX];
    if (argv && argv[0] && strchr(argv[0], '/')) {
        char tmp[PATH_MAX];
        strncpy(tmp, argv[0], sizeof(tmp) - 1);
        char *dir = dirname(tmp);
        snprintf(buf, sizeof(buf), "%s/%s", dir, KERNEL_BINARY);
        return buf;
    }
    return KERNEL_BINARY;
}

static int yai_init_system_shm() {
    char shm_path[128];
    // Il Vault di sistema è unico e globale per l'istanza del Kernel
    snprintf(shm_path, sizeof(shm_path), "%s%s", SHM_VAULT_PREFIX, SYSTEM_WS);

    shm_unlink(shm_path);
    int fd = shm_open(shm_path, O_CREAT | O_RDWR, 0666);
    if (fd == -1) return -1;

    if (ftruncate(fd, sizeof(yai_vault_t)) != 0) {
        close(fd);
        return -2;
    }

    yai_vault_t *v = mmap(NULL, sizeof(yai_vault_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (v == MAP_FAILED) {
        close(fd);
        return -3;
    }

    memset(v, 0, sizeof(yai_vault_t));
    v->status = YAI_STATE_PREBOOT;
    strncpy(v->workspace_id, SYSTEM_WS, MAX_WS_ID - 1);
    
    printf("[BOOT] Global System Vault allocated at %s\n", shm_path);

    munmap(v, sizeof(yai_vault_t));
    close(fd);
    return 0;
}

int main(int argc, char **argv) {
    (void)argc;
    printf("\033[1;33m--- YAI AGNOSTIC BOOTSTRAP (ADR-002) ---\033[0m\n");

    // 1. Preboot Invariants (Agnostici)
    yai_vault_t boot_ctx = {0};
    strncpy(boot_ctx.workspace_id, SYSTEM_WS, MAX_WS_ID - 1);

    if (yai_run_preboot_checks() != 0) {
        fprintf(stderr, "[FATAL] Environment security violation.\n");
        return EXIT_FAILURE;
    }

    // 2. Discovery: Qui creiamo le directory BASE (~/.yai/run/dev, etc.)
    // ma il socket principale sarà quello di controllo globale.
    yai_discover_environment(&boot_ctx);

    // 3. System SHM: Inizializziamo solo il piano di controllo
    if (yai_init_system_shm() != 0) {
        fprintf(stderr, "[FATAL] Failed to initialize System Plane SHM.\n");
        return EXIT_FAILURE;
    }

    printf("[BOOT] Environment discovery complete. Ready for Kernel takeover.\n");
    fflush(stdout);

    // 4. Exec Kernel: Passiamo al Kernel il controllo totale.
    // Il Kernel non riceverà più un --ws fisso, ma gestirà i socket dinamicamente.
    const char *kernel_bin = resolve_kernel_path(argv);
    
    // Il Kernel ora parte in modalità "Master"
    char *kernel_args[] = { (char *)kernel_bin, "--master", NULL };

    printf("[BOOT] Executing: %s --master\n", kernel_bin);

    if (execvp(kernel_bin, kernel_args) == -1) {
        perror("[FATAL] Kernel handoff failed");
        return EXIT_FAILURE;
    }

    return EXIT_FAILURE;
}