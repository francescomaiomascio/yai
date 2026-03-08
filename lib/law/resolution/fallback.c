#include "../internal.h"

int yai_law_apply_fallback(const yai_law_discovery_result_t *discovery, yai_law_effect_t *effect) {
  if (!discovery || !effect) return -1;
  if (discovery->ambiguous && *effect == YAI_LAW_EFFECT_ALLOW) {
    *effect = YAI_LAW_EFFECT_REVIEW_REQUIRED;
  }
  return 0;
}
