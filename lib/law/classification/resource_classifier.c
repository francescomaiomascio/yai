#include "../internal.h"

#include <string.h>

int yai_law_classify_resource(const char *payload, char *out, size_t out_cap) {
  const char *v = "workspace";
  if (!payload || !out || out_cap == 0) return -1;

  if (strstr(payload, "endpoint") || strstr(payload, "http")) v = "external_endpoint";
  else if (strstr(payload, "s3") || strstr(payload, "bucket")) v = "object_storage_bucket";
  else if (strstr(payload, "github") || strstr(payload, "issue")) v = "external_repository";
  else if (strstr(payload, "dataset")) v = "dataset";
  else if (strstr(payload, "params") || strstr(payload, "experiment")) v = "experiment_config";

  return yai_law_safe_snprintf(out, out_cap, "%s", v);
}
