#include <yai/law/evidence_map.h>

#include "../internal.h"

#include <string.h>

int yai_law_decision_to_evidence(const yai_law_decision_t *decision,
                                 const char *trace_id,
                                 const char *provider,
                                 const char *resource,
                                 const char *authority_context,
                                 yai_law_evidence_envelope_t *out) {
  if (!decision || !trace_id || !out) return -1;
  memset(out, 0, sizeof(*out));

  (void)yai_law_safe_snprintf(out->trace_id, sizeof(out->trace_id), "%s", trace_id);
  (void)yai_law_safe_snprintf(out->decision_id, sizeof(out->decision_id), "%s", decision->decision_id);
  (void)yai_law_safe_snprintf(out->domain_id, sizeof(out->domain_id), "%s", decision->domain_id);
  (void)yai_law_safe_snprintf(out->final_effect, sizeof(out->final_effect), "%s", yai_law_effect_name(decision->final_effect));
  (void)yai_law_safe_snprintf(out->provider, sizeof(out->provider), "%s", provider ? provider : "unknown");
  (void)yai_law_safe_snprintf(out->resource, sizeof(out->resource), "%s", resource ? resource : "unknown");
  (void)yai_law_safe_snprintf(out->authority_context, sizeof(out->authority_context), "%s", authority_context ? authority_context : "unknown");

  return 0;
}
