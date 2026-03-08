#include "../internal.h"

#include <string.h>

int yai_law_classify_provider(const char *payload, char *out, size_t out_cap) {
  const char *v = "provider.default";
  if (!payload || !out || out_cap == 0) return -1;

  if (strstr(payload, "curl")) v = "curl";
  else if (strstr(payload, "otel")) v = "otel-exporter";
  else if (strstr(payload, "s3")) v = "aws-s3";
  else if (strstr(payload, "github")) v = "github-api";
  else if (strstr(payload, "experiment") || strstr(payload, "params")) v = "experiment-runner";

  return yai_law_safe_snprintf(out, out_cap, "%s", v);
}
