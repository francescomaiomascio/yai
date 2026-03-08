#include "../internal.h"

#include <string.h>
#include <time.h>

static void add_rule(yai_law_effective_stack_t *stack, const char *id) {
  if (!stack || !id) return;
  if (stack->applied_rule_count >= YAI_LAW_RULE_MAX) return;
  (void)yai_law_safe_snprintf(stack->applied_rules[stack->applied_rule_count],
                              sizeof(stack->applied_rules[stack->applied_rule_count]),
                              "%s", id);
  stack->applied_rule_count++;
}

static void add_compliance(yai_law_effective_stack_t *stack, const char *id) {
  if (!stack || !id) return;
  if (stack->compliance_count >= YAI_LAW_COMPLIANCE_MAX) return;
  (void)yai_law_safe_snprintf(stack->compliance_layers[stack->compliance_count],
                              sizeof(stack->compliance_layers[stack->compliance_count]),
                              "%s", id);
  stack->compliance_count++;
}

int yai_law_stack_build(const yai_law_runtime_t *rt,
                        const yai_law_discovery_result_t *discovery,
                        const yai_law_classification_ctx_t *ctx,
                        yai_law_effective_stack_t *stack,
                        yai_law_effect_t *effect,
                        char *rationale,
                        size_t rationale_cap) {
  (void)rt;
  if (!discovery || !ctx || !stack || !effect) return -1;

  memset(stack, 0, sizeof(*stack));
  (void)yai_law_safe_snprintf(stack->stack_id, sizeof(stack->stack_id), "stack-%ld", (long)time(NULL));
  (void)yai_law_safe_snprintf(stack->domain_id, sizeof(stack->domain_id), "%s", discovery->domain_id);

  if (strcmp(discovery->domain_id, "D1-digital") == 0) {
    add_compliance(stack, "gdpr-eu");
    add_compliance(stack, "retention-governance");
    add_compliance(stack, "security-supply-chain");

    if (!ctx->has_authority_contract && (strcmp(ctx->action, "egress") == 0 || strcmp(ctx->action, "publish") == 0)) {
      add_rule(stack, "D1-digital.deny.uncontracted-egress");
      *effect = YAI_LAW_EFFECT_DENY;
      (void)yai_law_safe_snprintf(rationale, rationale_cap, "%s", "uncontracted external egress/publication");
    } else if (strstr(ctx->provider, "github")) {
      add_rule(stack, "D1-digital.review.github-comment");
      *effect = YAI_LAW_EFFECT_REVIEW_REQUIRED;
      (void)yai_law_safe_snprintf(rationale, rationale_cap, "%s", "external publication requires review");
    } else {
      add_rule(stack, "D1-digital.baseline.egress-review");
      *effect = YAI_LAW_EFFECT_REVIEW_REQUIRED;
      (void)yai_law_safe_snprintf(rationale, rationale_cap, "%s", "digital baseline review pathway");
    }
  } else {
    add_compliance(stack, "ai-act");
    add_compliance(stack, "retention-governance");

    if (!ctx->has_params_hash && (strstr(ctx->action, "experiment") || strstr(ctx->action, "parameter"))) {
      add_rule(stack, "D8-scientific.baseline.lock-required");
      *effect = YAI_LAW_EFFECT_DENY;
      (void)yai_law_safe_snprintf(rationale, rationale_cap, "%s", "missing params lock for scientific run");
    } else if (ctx->black_box_mode) {
      add_rule(stack, "D8-scientific.baseline.review-black-box");
      *effect = YAI_LAW_EFFECT_REVIEW_REQUIRED;
      (void)yai_law_safe_snprintf(rationale, rationale_cap, "%s", "black-box mode requires review");
    } else {
      add_rule(stack, "D8-scientific.review.parameter-lock-override");
      *effect = YAI_LAW_EFFECT_ALLOW;
      (void)yai_law_safe_snprintf(rationale, rationale_cap, "%s", "scientific baseline allows execution");
    }
  }

  (void)yai_law_safe_snprintf(stack->precedence_trace,
                              sizeof(stack->precedence_trace),
                              "%s",
                              "deny > quarantine > review_required > allow");
  return 0;
}
