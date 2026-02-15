// kernel/src/core/control_transport.c
#include "control_transport.h"

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

static int g_control_fd = -1;

/* ============================================================
   INTERNAL HELPERS
   ============================================================ */

static void best_effort_cloexec(int fd) {
#ifdef FD_CLOEXEC
    if (fd < 0) return;
    int flags = fcntl(fd, F_GETFD);
    if (flags >= 0)
        (void)fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
#else
    (void)fd;
#endif
}

static int read_all(int fd, void *buf, size_t n) {
    char *p = (char *)buf;
    size_t off = 0;

    while (off < n) {
        ssize_t r = read(fd, p + off, n - off);
        if (r <= 0) {
            if (r < 0 && errno == EINTR) continue;
            return YAI_CTL_ERR_READ;
        }
        off += (size_t)r;
    }
    return YAI_CTL_OK;
}

static int write_all(int fd, const void *buf, size_t n) {
    const char *p = (const char *)buf;
    size_t off = 0;

    while (off < n) {
        ssize_t w = write(fd, p + off, n - off);
        if (w < 0) {
            if (errno == EINTR) continue;
            return YAI_CTL_ERR_WRITE;
        }
        off += (size_t)w;
    }
    return YAI_CTL_OK;
}

/* ============================================================
   LISTEN / ACCEPT
   ============================================================ */

int yai_control_listen(const char *path) {
    if (!path || path[0] == '\0')
        return YAI_CTL_ERR_ARG;

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;

    size_t plen = strlen(path);
    if (plen >= sizeof(addr.sun_path))
        return YAI_CTL_ERR_ARG;

    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);

    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0)
        return YAI_CTL_ERR_SOCKET;

    if (g_control_fd >= 0) {
        close(g_control_fd);
        g_control_fd = -1;
    }

    (void)unlink(path);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        close(fd);
        return YAI_CTL_ERR_BIND;
    }

    (void)chmod(path, 0600);

    if (listen(fd, YAI_CONTROL_BACKLOG) < 0) {
        close(fd);
        return YAI_CTL_ERR_LISTEN;
    }

    g_control_fd = fd;
    best_effort_cloexec(g_control_fd);

    fprintf(stderr, "[CONTROL] Listening at %s\n", path);
    return YAI_CTL_OK;
}

int yai_control_accept(void) {
    if (g_control_fd < 0)
        return YAI_CTL_ERR_ACCEPT;

    for (;;) {
        int cfd = accept(g_control_fd, NULL, NULL);
        if (cfd >= 0) {
            best_effort_cloexec(cfd);
            return cfd;
        }
        if (errno == EINTR) continue;
        return YAI_CTL_ERR_ACCEPT;
    }
}

/* ============================================================
   FRAME READ (BINARY ENVELOPE V1)
   ============================================================ */

ssize_t yai_control_read_frame(
    int fd,
    yai_rpc_envelope_t *env,
    char *payload_buf,
    size_t payload_cap
) {
    if (fd < 0 || !env)
        return YAI_CTL_ERR_ARG;

    /* 1️⃣ read envelope */
    int rc = read_all(fd, env, sizeof(yai_rpc_envelope_t));
    if (rc != YAI_CTL_OK)
        return rc;

    /* 2️⃣ validate header */
    if (env->magic != YAI_FRAME_MAGIC)
        return YAI_CTL_ERR_READ;

    if (env->version != YAI_PROTOCOL_VERSION)
        return YAI_CTL_ERR_READ;

    if (env->payload_len > YAI_MAX_PAYLOAD)
        return YAI_CTL_ERR_OVERFLOW;

    if (env->payload_len > payload_cap)
        return YAI_CTL_ERR_OVERFLOW;

    /* 3️⃣ read payload */
    if (env->payload_len > 0) {
        rc = read_all(fd, payload_buf, env->payload_len);
        if (rc != YAI_CTL_OK)
            return rc;

        payload_buf[env->payload_len] = '\0'; // convenience
    }

    return (ssize_t)env->payload_len;
}

/* ============================================================
   FRAME WRITE
   ============================================================ */

int yai_control_write_frame(
    int fd,
    const yai_rpc_envelope_t *env,
    const char *payload
) {
    if (fd < 0 || !env)
        return YAI_CTL_ERR_ARG;

    int rc = write_all(fd, env, sizeof(yai_rpc_envelope_t));
    if (rc != YAI_CTL_OK)
        return rc;

    if (env->payload_len > 0 && payload) {
        rc = write_all(fd, payload, env->payload_len);
        if (rc != YAI_CTL_OK)
            return rc;
    }

    return YAI_CTL_OK;
}

/* ============================================================
   CLOSE
   ============================================================ */

void yai_control_close_fd(int fd) {
    if (fd >= 0)
        (void)close(fd);
}

void yai_control_close(void) {
    if (g_control_fd >= 0) {
        close(g_control_fd);
        g_control_fd = -1;
    }
}
