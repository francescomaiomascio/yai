#include "../internal.h"

int yai_law_decision_to_audit_blob(const yai_law_decision_t *decision, char *out, size_t out_cap) {
  if (!decision || !out || out_cap == 0) return -1;
  return yai_law_safe_snprintf(out,
                               out_cap,
                               "{\"decision_id\":\"%s\",\"domain_id\":\"%s\",\"effect\":\"%s\",\"rationale\":\"%s\"}",
                               decision->decision_id,
                               decision->domain_id,
                               yai_law_effect_name(decision->final_effect),
                               decision->rationale);
}
