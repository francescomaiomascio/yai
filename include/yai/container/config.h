#pragma once

#include <stdint.h>

typedef struct {
  uint64_t limits_class;
  uint64_t isolation_profile;
  uint64_t policy_profile;
  uint64_t grants_profile;
  uint64_t runtime_profile;
} yai_container_config_t;

void yai_container_config_defaults(yai_container_config_t *config);
