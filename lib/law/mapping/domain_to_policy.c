#include "../internal.h"

#include <string.h>

int yai_law_domain_to_policy_pack(const char *domain_id, const char *action, char *out, size_t out_cap) {
  if (!domain_id || !action || !out || out_cap == 0) return -1;
  if (strcmp(domain_id, "D1-digital") == 0) {
    if (strcmp(action, "egress") == 0 || strcmp(action, "publish") == 0)
      return yai_law_safe_snprintf(out, out_cap, "%s", "D1-digital.baseline");
    return yai_law_safe_snprintf(out, out_cap, "%s", "D1-digital.review");
  }
  if (strcmp(domain_id, "D8-scientific") == 0) {
    return yai_law_safe_snprintf(out, out_cap, "%s", "D8-scientific.baseline");
  }
  return yai_law_safe_snprintf(out, out_cap, "%s", "unknown");
}
