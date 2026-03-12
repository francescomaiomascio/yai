#pragma once

#include "config.h"
#include "identity.h"
#include "lifecycle.h"
#include "root.h"
#include "session.h"
#include "state.h"

typedef struct {
  yai_container_identity_t identity;
  yai_container_config_t config;
  yai_container_lifecycle_t lifecycle;
  yai_container_root_t root;
  yai_container_session_domain_t session_domain;
  yai_container_state_t state;
} yai_container_record_t;

int yai_container_register(const yai_container_record_t *record);
int yai_container_get(const char *container_id, yai_container_record_t *out_record);
int yai_container_set_lifecycle(const char *container_id,
                                yai_container_lifecycle_state_t next_state,
                                int64_t at);
