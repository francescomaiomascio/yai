#include "../internal.h"

int yai_law_map_policy_to_effect(yai_law_effect_t in_effect, yai_law_effect_t *out_effect) {
  if (!out_effect) return -1;
  switch (in_effect) {
    case YAI_LAW_EFFECT_DENY:
    case YAI_LAW_EFFECT_QUARANTINE:
    case YAI_LAW_EFFECT_REVIEW_REQUIRED:
    case YAI_LAW_EFFECT_ALLOW:
    case YAI_LAW_EFFECT_DEGRADE:
      *out_effect = in_effect;
      break;
    case YAI_LAW_EFFECT_REQUIRE_JUSTIFICATION:
      *out_effect = YAI_LAW_EFFECT_REVIEW_REQUIRED;
      break;
    case YAI_LAW_EFFECT_UNKNOWN:
    default:
      *out_effect = YAI_LAW_EFFECT_REVIEW_REQUIRED;
      break;
  }
  return 0;
}
