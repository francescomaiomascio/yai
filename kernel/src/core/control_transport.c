#include "control_transport.h"

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int g_control_fd = -1;

int yai_control_listen(const char *path) {

    struct sockaddr_un addr;

    g_control_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (g_control_fd < 0) return -1;

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);

    unlink(path);

    if (bind(g_control_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        return -2;

    chmod(path, 0600);

    if (listen(g_control_fd, 5) < 0)
        return -3;

    printf("[CONTROL] Listening at %s\n", path);
    return 0;
}

int yai_control_accept(void) {
    if (g_control_fd < 0) return -1;
    return accept(g_control_fd, NULL, NULL);
}

ssize_t yai_control_read_line(int fd, char *buf, size_t cap) {
    size_t i = 0;
    char c;

    while (i < cap - 1) {
        ssize_t n = read(fd, &c, 1);
        if (n <= 0) break;

        if (c == '\n') break;

        buf[i++] = c;
    }

    buf[i] = '\0';
    return i;
}

int yai_control_write_line(int fd, const char *line) {
    if (!line) return -1;

    write(fd, line, strlen(line));
    write(fd, "\n", 1);
    return 0;
}

void yai_control_close(void) {
    if (g_control_fd >= 0) {
        close(g_control_fd);
        g_control_fd = -1;
    }
}
