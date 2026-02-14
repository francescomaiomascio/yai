#include "yai_vault.h"
#include "yai_kernel.h"
#include "kernel.h"
#include <protocol/transport.h>
#include <protocol/yai_protocol_ids.h>
#include "transport.h"         
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    const char *ws_id = "default";

    // 1. Recupera il workspace passato dal Bootstrap
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--ws") == 0 && i + 1 < argc) {
            ws_id = argv[i + 1];
        }
    }

    printf("\n\033[1;34m[YAI]\033[0m --- \033[1;32mSOVEREIGN KERNEL RUNTIME V1.0\033[0m ---\n");
    
    // 2. Costruiamo il path del socket dinamicamente come fa la CLI
    char socket_path[1024];
    const char* home = getenv("HOME");
    snprintf(socket_path, sizeof(socket_path), "%s/.yai/run/%s/control.sock", home, ws_id);

    // 3. Inizializza il trasporto con il path CORRETTO
    // Dobbiamo modificare yai_transport_init affinché accetti il path!
    if (yai_transport_init_at(socket_path) != 0) {
        fprintf(stderr, "\033[1;31m[FATAL]\033[0m Transport Plane failed on %s\n", socket_path);
        return 1;
    }

    printf("\033[1;34m[YAI]\033[0m Root Plane online: %s\n", socket_path);
    printf("\033[1;34m[YAI]\033[0m Awaiting secure RPC envelopes...\n\n");

    for (;;) {
        yai_transport_serve_once();
    }
    return 0;
}