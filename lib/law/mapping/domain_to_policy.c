#include "../internal.h"

#include <string.h>

int yai_law_domain_to_policy_pack(const char *domain_id, const char *action, char *out, size_t out_cap) {
  if (!domain_id || !action || !out || out_cap == 0) return -1;
  if (strcmp(domain_id, "D1-digital") == 0) {
    if (strcmp(action, "egress") == 0 || strcmp(action, "publish") == 0)
      return yai_law_safe_snprintf(out, out_cap, "%s", "D1-digital.baseline");
    return yai_law_safe_snprintf(out, out_cap, "%s", "D1-digital.review");
  }
  if (strcmp(domain_id, "D5-economic") == 0) {
    if (strcmp(action, "authorize") == 0)
      return yai_law_safe_snprintf(out, out_cap, "%s", "D5-economic.payments.baseline");
    if (strcmp(action, "settle") == 0)
      return yai_law_safe_snprintf(out, out_cap, "%s", "D5-economic.settlements.review");
    return yai_law_safe_snprintf(out, out_cap, "%s", "D5-economic.review");
  }
  if (strcmp(domain_id, "D8-scientific") == 0) {
    return yai_law_safe_snprintf(out, out_cap, "%s", "D8-scientific.baseline");
  }
  return yai_law_safe_snprintf(out, out_cap, "%s", "unknown");
}
