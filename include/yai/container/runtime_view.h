#pragma once

#include "bindings.h"
#include "grants_view.h"
#include "policy_view.h"
#include "state.h"

typedef struct {
  yai_container_state_t state;
  yai_container_policy_view_t policy_view;
  yai_container_grants_view_t grants_view;
  yai_container_bindings_t bindings;
} yai_container_runtime_view_t;

int yai_container_runtime_view_get(const char *container_id,
                                   yai_container_runtime_view_t *out_view);
