#include "../internal.h"

#include <stdio.h>

int yai_law_compatibility_check(yai_law_runtime_t *rt, char *err, size_t err_cap) {
  char path[512];
  char json[2048];

  if (!rt) return -1;

  if (yai_law_safe_snprintf(path, sizeof(path), "%s/COMPATIBILITY.json", rt->root) != 0) {
    return -1;
  }
  if (yai_law_read_text_file(path, json, sizeof(json)) != 0) {
    if (err && err_cap) (void)yai_law_safe_snprintf(err, err_cap, "missing compatibility file: %s", path);
    return -1;
  }

  (void)yai_law_json_extract_string(json, "compatibility_profile", rt->compatibility.profile, sizeof(rt->compatibility.profile));
  (void)yai_law_json_extract_string(json, "law_version", rt->compatibility.law_version, sizeof(rt->compatibility.law_version));

  if (rt->compatibility.profile[0] == '\0') {
    (void)yai_law_safe_snprintf(rt->compatibility.profile, sizeof(rt->compatibility.profile), "%s", "runtime-consumer.v1");
  }

  if (yai_law_safe_snprintf(path, sizeof(path), "%s/domains/index/domains.index.json", rt->root) != 0 ||
      yai_law_read_text_file(path, json, sizeof(json)) != 0) {
    if (err && err_cap) (void)yai_law_safe_snprintf(err, err_cap, "missing domain index");
    return -1;
  }

  if (yai_law_safe_snprintf(path, sizeof(path), "%s/compliance/index/compliance.index.json", rt->root) != 0 ||
      yai_law_read_text_file(path, json, sizeof(json)) != 0) {
    if (err && err_cap) (void)yai_law_safe_snprintf(err, err_cap, "missing compliance index");
    return -1;
  }

  return 0;
}
