#pragma once

#include <stdint.h>

typedef struct {
  uint64_t container_session_scope;
  uint64_t bound_session_count;
  uint64_t last_bound_session_id;
  uint64_t last_bound_at;
  uint8_t privileged_access;
  uint8_t bound;
} yai_container_session_domain_t;
