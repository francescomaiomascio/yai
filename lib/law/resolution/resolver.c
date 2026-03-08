#include <yai/law/resolver.h>

#include "../internal.h"

#include <string.h>
#include <time.h>

int yai_law_apply_precedence(yai_law_effect_t *effect);
int yai_law_apply_fallback(const yai_law_discovery_result_t *discovery, yai_law_effect_t *effect);
int yai_law_resolve_conflicts(yai_law_effect_t *effect);
int yai_law_effective_stack_finalize(yai_law_effective_stack_t *stack);
int yai_law_map_policy_to_effect(yai_law_effect_t in_effect, yai_law_effect_t *out_effect);
int yai_law_decision_to_audit_blob(const yai_law_decision_t *decision, char *out, size_t out_cap);

int yai_law_resolve_control_call(const char *ws_id,
                                 const char *payload,
                                 const char *trace_id,
                                 yai_law_resolution_output_t *out,
                                 char *err,
                                 size_t err_cap) {
  yai_law_runtime_t runtime;
  yai_law_classification_ctx_t ctx;
  yai_law_discovery_result_t discovery;
  yai_law_effect_t base_effect = YAI_LAW_EFFECT_UNKNOWN;
  yai_law_effect_t final_effect = YAI_LAW_EFFECT_UNKNOWN;
  char rationale[192] = {0};

  if (!payload || !out) return -1;
  memset(out, 0, sizeof(*out));

  if (yai_law_load_runtime(&runtime, err, err_cap) != 0) {
    return -1;
  }
  if (yai_law_classify_event(ws_id, payload, &ctx) != 0) {
    if (err && err_cap) (void)yai_law_safe_snprintf(err, err_cap, "%s", "classification_failed");
    return -1;
  }
  if (yai_law_discover_domain(&ctx, &discovery) != 0) {
    if (err && err_cap) (void)yai_law_safe_snprintf(err, err_cap, "%s", "discovery_failed");
    return -1;
  }

  if (yai_law_stack_build(&runtime, &discovery, &ctx, &out->decision.stack, &base_effect, rationale, sizeof(rationale)) != 0) {
    if (err && err_cap) (void)yai_law_safe_snprintf(err, err_cap, "%s", "stack_build_failed");
    return -1;
  }

  if (yai_law_map_policy_to_effect(base_effect, &final_effect) != 0) {
    if (err && err_cap) (void)yai_law_safe_snprintf(err, err_cap, "%s", "effect_mapping_failed");
    return -1;
  }

  (void)yai_law_apply_precedence(&final_effect);
  (void)yai_law_apply_fallback(&discovery, &final_effect);
  (void)yai_law_resolve_conflicts(&final_effect);
  (void)yai_law_effective_stack_finalize(&out->decision.stack);

  (void)yai_law_safe_snprintf(out->decision.decision_id, sizeof(out->decision.decision_id), "dec-%ld", (long)time(NULL));
  (void)yai_law_safe_snprintf(out->decision.domain_id, sizeof(out->decision.domain_id), "%s", discovery.domain_id);
  out->decision.final_effect = final_effect;
  (void)yai_law_safe_snprintf(out->decision.rationale, sizeof(out->decision.rationale), "%s", rationale[0] ? rationale : discovery.rationale);

  (void)yai_law_safe_snprintf(out->decision.evidence_requirements[0], sizeof(out->decision.evidence_requirements[0]), "%s", "resolution_trace");
  (void)yai_law_safe_snprintf(out->decision.evidence_requirements[1], sizeof(out->decision.evidence_requirements[1]), "%s", "decision_record");
  out->decision.evidence_requirement_count = 2;

  if (yai_law_decision_to_evidence(&out->decision,
                                   (trace_id && trace_id[0]) ? trace_id : "trace-missing",
                                   ctx.provider,
                                   ctx.resource,
                                   ctx.has_authority_contract ? "contracted" : "missing_contract",
                                   &out->evidence) != 0) {
    if (err && err_cap) (void)yai_law_safe_snprintf(err, err_cap, "%s", "evidence_mapping_failed");
    return -1;
  }

  if (yai_law_build_trace_json(&ctx, &discovery, &out->decision, out->trace_json, sizeof(out->trace_json)) != 0) {
    if (err && err_cap) (void)yai_law_safe_snprintf(err, err_cap, "%s", "trace_build_failed");
    return -1;
  }

  return 0;
}
