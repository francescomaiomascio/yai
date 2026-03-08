#include <stdio.h>
#include <string.h>

#include <yai/law/resolver.h>
#include <yai/law/policy_effects.h>

int main(void) {
  yai_law_resolution_output_t out;
  char err[256] = {0};

  if (yai_law_resolve_control_call("ws-a", "{\"command\":\"curl\",\"resource\":\"endpoint\"}", "trace-a", &out, err, sizeof(err)) != 0) {
    fprintf(stderr, "resolution failed: %s\n", err);
    return 1;
  }
  if (out.decision.final_effect != YAI_LAW_EFFECT_DENY && out.decision.final_effect != YAI_LAW_EFFECT_REVIEW_REQUIRED) return 1;

  if (yai_law_resolve_control_call("ws-b", "{\"command\":\"experiment.run\",\"params_hash\":\"ok\",\"dataset\":\"d\"}", "trace-b", &out, err, sizeof(err)) != 0) return 1;
  if (strcmp(out.decision.domain_id, "D8-scientific") != 0) return 1;

  puts("resolution: ok");
  return 0;
}
