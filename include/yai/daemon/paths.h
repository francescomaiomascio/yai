#pragma once

#include <yai/daemon/config.h>

typedef struct yai_daemon_paths {
  char home[YAI_DAEMON_PATH_MAX];
  char config_dir[YAI_DAEMON_PATH_MAX];
  char state_dir[YAI_DAEMON_PATH_MAX];
  char log_dir[YAI_DAEMON_PATH_MAX];
  char spool_dir[YAI_DAEMON_PATH_MAX];
  char bindings_dir[YAI_DAEMON_PATH_MAX];
  char identity_dir[YAI_DAEMON_PATH_MAX];
  char run_dir[YAI_DAEMON_PATH_MAX];
  char pid_file[YAI_DAEMON_PATH_MAX];
  char health_file[YAI_DAEMON_PATH_MAX];
  char instance_file[YAI_DAEMON_PATH_MAX];
} yai_daemon_paths_t;

int yai_daemon_paths_build(const yai_daemon_config_t *cfg,
                           yai_daemon_paths_t *paths);
int yai_daemon_paths_ensure(const yai_daemon_paths_t *paths);
