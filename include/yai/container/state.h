#pragma once

#include <stdint.h>

#include "lifecycle.h"

typedef struct {
  uint64_t health_flags;
  uint64_t resource_class;
  uint64_t attachments;
  uint64_t services_online;
  uint64_t daemon_bindings;
  uint64_t network_bindings;
  uint64_t recovery_reason_flags;
  int64_t updated_at;
  yai_container_lifecycle_state_t lifecycle_state;
} yai_container_state_t;

void yai_container_state_defaults(yai_container_state_t *state);
