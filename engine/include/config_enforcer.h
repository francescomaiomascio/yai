#ifndef YAI_CONFIG_ENFORCER_H
#define YAI_CONFIG_ENFORCER_H

#include <stdbool.h>
#include <stdint.h> // <--- INDISPENSABILE PER uint16_t

typedef struct {
    char storage_backend[32];
    uint16_t max_parallel_agents;
    bool enforce_tla_safety;
} HardenedConfig;

bool yai_config_enforce_limits(HardenedConfig* cfg);

#endif