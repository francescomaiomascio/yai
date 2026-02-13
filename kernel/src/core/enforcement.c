#include "kernel.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static bool contains_token(const char *s, const char *token) {
    return s && token && strstr(s, token) != NULL;
}

static bool extract_ws_id(const char *line, char *out, size_t cap) {
    const char *start = strstr(line, "\"ws_id\":\"");
    if (!start) return false;

    start += 9; // skip "ws_id":" 
    const char *end = strchr(start, '"');
    if (!end) return false;

    size_t len = end - start;
    if (len == 0 || len >= cap) return false;

    strncpy(out, start, len);
    out[len] = '\0';
    return true;
}

int yai_validate_envelope_v1(
    const char *line,
    const char *expected_ws,
    char *out_request_type,
    size_t req_cap
) {
    if (!line) return -1;

    // 1. Version check
    if (!contains_token(line, "\"v\":1") &&
        !contains_token(line, "\"v\": 1"))
        return -2;

    // 2. ws_id required
    char ws_buf[64] = {0};
    if (!extract_ws_id(line, ws_buf, sizeof(ws_buf)))
        return -3;

    if (strcmp(ws_buf, expected_ws) != 0)
        return -3;

    // 3. request.type extraction
    const char *type_pos = strstr(line, "\"type\":\"");
    if (!type_pos) return -4;

    type_pos += 8; // skip "type":"
    const char *type_end = strchr(type_pos, '"');
    if (!type_end) return -4;

    size_t len = type_end - type_pos;
    if (len == 0 || len >= req_cap) return -4;

    strncpy(out_request_type, type_pos, len);
    out_request_type[len] = '\0';

    // 4. Allowed types only
    if (strcmp(out_request_type, "ping") == 0)
        return 0;

    if (strcmp(out_request_type, "protocol_handshake") == 0)
        return 0;

    if (strcmp(out_request_type, "status") == 0)
        return 0;

    return -5;
}
