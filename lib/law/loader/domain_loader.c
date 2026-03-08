#include "../internal.h"

#include <string.h>

int yai_law_load_domain_manifest(const yai_law_runtime_t *rt,
                                 const char *domain_id,
                                 char *out_json,
                                 size_t out_cap) {
  char path[512];
  int rc;
  const char *roots[] = {
    "control-families",
    "domain-specializations",
    "domains",
    "transitional/domain-family-seed",
  };
  size_t i;
  if (!rt || !domain_id || !out_json || out_cap == 0) return -1;
  for (i = 0; i < (sizeof(roots) / sizeof(roots[0])); ++i) {
    if (yai_law_safe_snprintf(path, sizeof(path), "%s/%s/%s/manifest.json", rt->root, roots[i], domain_id) != 0) {
      return -1;
    }
    rc = yai_law_read_text_file(path, out_json, out_cap);
    if (rc == 0) return 0;
  }
  return -1;
}
