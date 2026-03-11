#pragma once

#include <stddef.h>

#define YAI_DAEMON_PATH_MAX 512
#define YAI_DAEMON_LABEL_MAX 128
#define YAI_DAEMON_LEVEL_MAX 32
#define YAI_DAEMON_MODE_MAX 32

typedef struct yai_daemon_config {
  char home[YAI_DAEMON_PATH_MAX];
  char config_path[YAI_DAEMON_PATH_MAX];
  char owner_ref[YAI_DAEMON_PATH_MAX];
  char source_label[YAI_DAEMON_LABEL_MAX];
  char log_level[YAI_DAEMON_LEVEL_MAX];
  char mode[YAI_DAEMON_MODE_MAX];
  char bindings_manifest[YAI_DAEMON_PATH_MAX];
  unsigned int tick_ms;
  int max_ticks;
} yai_daemon_config_t;

int yai_daemon_config_defaults(yai_daemon_config_t *cfg);
int yai_daemon_config_apply_env(yai_daemon_config_t *cfg);
int yai_daemon_config_apply_file(yai_daemon_config_t *cfg, const char *path);
int yai_daemon_config_validate(const yai_daemon_config_t *cfg);

int yai_daemon_config_set_string(char *dst,
                                 size_t dst_cap,
                                 const char *value);

int yai_daemon_config_parse_uint(const char *raw, unsigned int *out);
int yai_daemon_config_parse_int(const char *raw, int *out);
