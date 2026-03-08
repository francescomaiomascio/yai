#include "../internal.h"

#include <stdlib.h>
#include <string.h>

int yai_law_load_domain_manifest(const yai_law_runtime_t *rt,
                                 const char *domain_id,
                                 char *out_json,
                                 size_t out_cap) {
  char path[512];
  int rc;
  const char *roots_primary[] = {
    "control-families",
    "domain-specializations",
    "domains"
  };
  const char *legacy_seed = "transitional/domain-family-seed";
  const char *allow_seed = getenv("YAI_LAW_ENABLE_TRANSITIONAL_SEED");
  size_t i;
  if (!rt || !domain_id || !out_json || out_cap == 0) return -1;
  for (i = 0; i < (sizeof(roots_primary) / sizeof(roots_primary[0])); ++i) {
    if (yai_law_safe_snprintf(path, sizeof(path), "%s/%s/%s/manifest.json", rt->root, roots_primary[i], domain_id) != 0) {
      return -1;
    }
    rc = yai_law_read_text_file(path, out_json, out_cap);
    if (rc == 0) return 0;
  }
  /* Transitional seed is opt-in only and never part of default runtime lookup. */
  if (allow_seed && strcmp(allow_seed, "1") == 0) {
    if (yai_law_safe_snprintf(path, sizeof(path), "%s/%s/%s/manifest.json", rt->root, legacy_seed, domain_id) != 0) {
      return -1;
    }
    rc = yai_law_read_text_file(path, out_json, out_cap);
    if (rc == 0) return 0;
  }
  return -1;
}
