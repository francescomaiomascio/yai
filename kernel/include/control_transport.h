#pragma once
#include <stddef.h>
#include <sys/types.h>

int yai_control_listen(const char *control_sock_path);
int yai_control_accept(void);
ssize_t yai_control_read_line(int fd, char *buf, size_t cap);
int yai_control_write_line(int fd, const char *line);
void yai_control_close(void);
