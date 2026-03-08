#include "../internal.h"

int yai_law_event_to_domain_bridge(const yai_law_classification_ctx_t *ctx,
                                   const yai_law_discovery_result_t *discovery,
                                   char *out,
                                   size_t out_cap) {
  (void)ctx;
  if (!discovery || !out || out_cap == 0) return -1;
  /* Transitional bridge API name: flow is event -> classification -> family -> specialization -> domain_id compatibility. */
  return yai_law_safe_snprintf(out, out_cap, "%s", discovery->domain_id);
}
