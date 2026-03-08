#include "../internal.h"

int yai_law_dump_effective_stack(const yai_law_effective_stack_t *stack, char *out, size_t out_cap) {
  if (!stack || !out || out_cap == 0) return -1;
  return yai_law_safe_snprintf(out,
                               out_cap,
                               "stack=%s domain=%s rules=%d compliance=%d precedence=%s",
                               stack->stack_id,
                               stack->domain_id,
                               stack->applied_rule_count,
                               stack->compliance_count,
                               stack->precedence_trace);
}
