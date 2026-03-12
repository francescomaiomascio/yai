#include <string.h>

#include "yai/container/config.h"

void yai_container_config_defaults(yai_container_config_t *config) {
  if (!config) {
    return;
  }
  memset(config, 0, sizeof(*config));
  config->limits_class = 1;
  config->isolation_profile = 1;
  config->policy_profile = 1;
  config->grants_profile = 1;
  config->runtime_profile = 1;
}
