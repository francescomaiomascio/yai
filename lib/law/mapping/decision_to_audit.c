#include "../internal.h"

int yai_law_decision_to_audit_blob(const yai_law_decision_t *decision, char *out, size_t out_cap) {
  if (!decision || !out || out_cap == 0) return -1;
  return yai_law_safe_snprintf(out,
                               out_cap,
                               "{\"decision_id\":\"%s\",\"family_id\":\"%s\",\"domain_id\":\"%s\",\"specialization_id\":\"%s\",\"effect\":\"%s\",\"rationale\":\"%s\",\"regulatory_overlay_count\":%d,\"sector_overlay_count\":%d,\"contextual_overlay_count\":%d,\"authority_profile\":\"%s\",\"evidence_profile\":\"%s\"}",
                               decision->decision_id,
                               decision->family_id,
                               decision->domain_id,
                               decision->specialization_id,
                               yai_law_effect_name(decision->final_effect),
                               decision->rationale,
                               decision->stack.regulatory_overlay_count,
                               decision->stack.sector_overlay_count,
                               decision->stack.contextual_overlay_count,
                               decision->stack.authority_profile,
                               decision->stack.evidence_profile);
}
