#include "../internal.h"

int yai_law_map_policy_to_effect(yai_law_effect_t in_effect, yai_law_effect_t *out_effect) {
  if (!out_effect) return -1;
  *out_effect = in_effect;
  return 0;
}
