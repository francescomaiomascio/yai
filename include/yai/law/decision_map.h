#pragma once

#include <yai/law/effective_stack.h>
#include <yai/law/policy_effects.h>

typedef struct yai_law_decision {
  char decision_id[64];
  char domain_id[64];
  yai_law_effect_t final_effect;
  char rationale[192];
  yai_law_effective_stack_t stack;
  char evidence_requirements[8][64];
  int evidence_requirement_count;
} yai_law_decision_t;
