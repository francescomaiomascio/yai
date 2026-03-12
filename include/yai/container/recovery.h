#pragma once

#include <stdint.h>

int yai_container_enter_recovery(const char *container_id, uint64_t reason_flags);
int yai_container_seal(const char *container_id, int64_t sealed_at);
int yai_container_restore(const char *container_id);
