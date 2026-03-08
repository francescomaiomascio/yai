#include "../internal.h"

#include <string.h>

int yai_law_classify_action(const char *payload, char *out, size_t out_cap) {
  const char *v = "transform";
  if (!payload || !out || out_cap == 0) return -1;

  if (strstr(payload, "curl") || strstr(payload, "egress") || strstr(payload, "otel") || strstr(payload, "s3")) {
    v = "egress";
  } else if (strstr(payload, "github") || strstr(payload, "comment") || strstr(payload, "publish")) {
    v = "publish";
  } else if (strstr(payload, "retrieve") || strstr(payload, "read")) {
    v = "retrieve";
  } else if (strstr(payload, "infer") || strstr(payload, "model")) {
    v = "infer";
  } else if (strstr(payload, "actuate")) {
    v = "actuate";
  } else if (strstr(payload, "experiment") || strstr(payload, "params")) {
    v = "run-experiment";
  }

  if (yai_law_safe_snprintf(out, out_cap, "%s", v) != 0) return -1;
  return 0;
}
