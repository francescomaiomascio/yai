#pragma once

#include <yai/law/discovery.h>

#define YAI_LAW_RULE_MAX 12
#define YAI_LAW_COMPLIANCE_MAX 8

typedef struct yai_law_effective_stack {
  char stack_id[64];
  char domain_id[64];
  char applied_rules[YAI_LAW_RULE_MAX][96];
  int applied_rule_count;
  char skipped_rules[YAI_LAW_RULE_MAX][96];
  int skipped_rule_count;
  char compliance_layers[YAI_LAW_COMPLIANCE_MAX][64];
  int compliance_count;
  char precedence_trace[192];
} yai_law_effective_stack_t;
