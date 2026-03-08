#include "../internal.h"

#include <string.h>

int yai_law_load_domain_manifest(const yai_law_runtime_t *rt,
                                 const char *domain_id,
                                 char *out_json,
                                 size_t out_cap) {
  char path[512];
  if (!rt || !domain_id || !out_json || out_cap == 0) return -1;
  if (yai_law_safe_snprintf(path, sizeof(path), "%s/domains/%s/manifest.json", rt->root, domain_id) != 0) {
    return -1;
  }
  return yai_law_read_text_file(path, out_json, out_cap);
}
