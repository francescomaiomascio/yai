#include "../internal.h"

int yai_law_build_trace_json(const yai_law_classification_ctx_t *ctx,
                             const yai_law_discovery_result_t *disc,
                             const yai_law_decision_t *decision,
                             char *out,
                             size_t out_cap) {
  if (!ctx || !disc || !decision || !out || out_cap == 0) return -1;
  return yai_law_safe_snprintf(
      out,
      out_cap,
      "{\"type\":\"yai.law.resolution_trace.v1\",\"action\":\"%s\",\"provider\":\"%s\",\"resource\":\"%s\",\"protocol\":\"%s\",\"matched_domain\":\"%s\",\"confidence\":%.3f,\"ambiguous\":%s,\"final_effect\":\"%s\",\"rationale\":\"%s\",\"precedence_trace\":\"%s\"}",
      ctx->action,
      ctx->provider,
      ctx->resource,
      ctx->protocol,
      disc->domain_id,
      disc->confidence,
      disc->ambiguous ? "true" : "false",
      yai_law_effect_name(decision->final_effect),
      decision->rationale,
      decision->stack.precedence_trace);
}
