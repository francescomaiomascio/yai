#include "../internal.h"

int yai_law_load_compliance_index(const yai_law_runtime_t *rt,
                                  char *out_json,
                                  size_t out_cap) {
  char path[512];
  if (!rt || !out_json || out_cap == 0) return -1;
  if (yai_law_safe_snprintf(path, sizeof(path), "%s/compliance/index/compliance.index.json", rt->root) != 0) {
    return -1;
  }
  return yai_law_read_text_file(path, out_json, out_cap);
}
