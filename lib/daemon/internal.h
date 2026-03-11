#pragma once

#include <stdarg.h>

int yai_daemon_write_file(const char *path, const char *payload);
int yai_daemon_mkdir_recursive(const char *path);
void yai_daemon_vlog(const char *instance_id,
                     const char *level,
                     const char *fmt,
                     va_list ap);
