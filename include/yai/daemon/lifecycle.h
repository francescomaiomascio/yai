#pragma once

#include <yai/daemon/runtime.h>

int yai_daemon_lifecycle_install_signals(void);
int yai_daemon_lifecycle_should_stop(void);
int yai_daemon_lifecycle_run_foreground(yai_daemon_runtime_t *rt);
