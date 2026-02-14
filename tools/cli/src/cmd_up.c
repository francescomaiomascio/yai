#include <stdio.h>   // Per printf, stderr, fprintf
#include <stdlib.h>  // Per system, exit
#include <unistd.h>  // Per sleep, access

#define YAI_OK 0

// Funzione dummy per il ping del socket (da implementare con connect())
int ping_root_socket() {
    // Verifica se il file del socket esiste come test primario
    if (access("/Users/francescomaiomascio/.yai/run/dev/control.sock", F_OK) != -1) {
        return YAI_OK;
    }
    return -1;
}

void cmd_up() {
    printf("\033[1;33m[UP]\033[0m Orchestrating Sovereign Runtime...\n");

    // 1. L0 -> L1: BOOT (che diventa KERNEL via execvp)
    if (ping_root_socket() != YAI_OK) { 
        printf("[UP] Root Plane offline. Launching yai-boot...\n");
        // Usiamo system() o spawn_process() per lanciare il boot in background
        if (system("yai-boot &") != 0) {
            fprintf(stderr, "[ERROR] Failed to ignite bootstrap.\n");
            return;
        }
        // Diamo tempo al Kernel di aprire il socket e creare la SHM
        sleep(2); 
    }

    // 2. L1 -> L2: ENGINE
    // Ora che il Root Plane è attivo, solleviamo l'Engine di sistema
    printf("[UP] Root Plane active. Igniting Engine...\n");
    if (system("yai-engine &") != 0) {
        fprintf(stderr, "[ERROR] Failed to launch Engine.\n");
        return;
    }

    printf("\n\033[1;32m✔ YAI Runtime is UP (Global Context)\033[0m\n");
    printf("Next step: Launch a workspace with 'yai-mind --ws <id>'\n");
}