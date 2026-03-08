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
  (void)yai_law_safe_snprintf(out->family_id, sizeof(out->family_id), "%s", decision->family_id);
  (void)yai_law_safe_snprintf(out->specialization_id, sizeof(out->specialization_id), "%s", decision->specialization_id);
  (void)yai_law_safe_snprintf(out->final_effect, sizeof(out->final_effect), "%s", yai_law_effect_name(decision->final_effect));
  (void)yai_law_safe_snprintf(out->provider, sizeof(out->provider), "%s", provider ? provider : "unknown");
  (void)yai_law_safe_snprintf(out->resource, sizeof(out->resource), "%s", resource ? resource : "unknown");
  (void)yai_law_safe_snprintf(out->authority_context, sizeof(out->authority_context), "%s", authority_context ? authority_context : "unknown");
  out->review_trace_required = decision->final_effect == YAI_LAW_EFFECT_REVIEW_REQUIRED ? 1 : 0;
  out->retention_required = 0;
  out->provenance_required = 0;
  out->approval_chain_required = 0;
  out->dependency_chain_required = 0;
  out->lawful_basis_required = 0;
  out->oversight_trace_required = 0;
  for (int i = 0; i < decision->evidence_requirement_count; ++i) {
    if (strstr(decision->evidence_requirements[i], "retention")) out->retention_required = 1;
    if (strstr(decision->evidence_requirements[i], "provenance")) out->provenance_required = 1;
    if (strstr(decision->evidence_requirements[i], "review_trace")) out->review_trace_required = 1;
    if (strstr(decision->evidence_requirements[i], "approval_chain")) out->approval_chain_required = 1;
    if (strstr(decision->evidence_requirements[i], "dependency_chain")) out->dependency_chain_required = 1;
    if (strstr(decision->evidence_requirements[i], "lawful_basis")) out->lawful_basis_required = 1;
    if (strstr(decision->evidence_requirements[i], "oversight_trace")) out->oversight_trace_required = 1;
  }

  return 0;
}
