#include <yai/governance/policy_effects.h>

const char *yai_law_effect_name(yai_law_effect_t effect) {
  switch (effect) {
    case YAI_LAW_EFFECT_ALLOW: return "allow";
    case YAI_LAW_EFFECT_DENY: return "deny";
    case YAI_LAW_EFFECT_QUARANTINE: return "quarantine";
    case YAI_LAW_EFFECT_REVIEW_REQUIRED: return "review_required";
    case YAI_LAW_EFFECT_DEGRADE: return "degrade";
    case YAI_LAW_EFFECT_REQUIRE_JUSTIFICATION: return "require_justification";
    default: return "unknown";
  }
}
