#ifndef YAI_STORAGE_GATE_H
#define YAI_STORAGE_GATE_H

#include <stdbool.h>
#include <stddef.h> // <--- AGGIUNGI QUESTO PER size_t

typedef enum {
    STORAGE_READ  = 0,
    STORAGE_WRITE = 1,
    STORAGE_ADMIN = 2
} StorageAccessLevel;

bool yai_storage_verify_access(const char* db_path, StorageAccessLevel level);
void yai_storage_audit_io(const char* op, size_t bytes);

#endif