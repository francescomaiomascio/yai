#include "../internal.h"

int yai_law_dump_discovery_result(const yai_law_discovery_result_t *disc, char *out, size_t out_cap) {
  if (!disc || !out || out_cap == 0) return -1;
  return yai_law_safe_snprintf(out,
                               out_cap,
                               "domain=%s confidence=%.3f ambiguous=%d rationale=%s",
                               disc->domain_id,
                               disc->confidence,
                               disc->ambiguous,
                               disc->rationale);
}
