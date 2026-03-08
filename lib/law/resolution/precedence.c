#include "../internal.h"

int yai_law_apply_precedence(yai_law_effect_t *effect) {
  if (!effect) return -1;
  /* Effects already computed in stack builder; hook left explicit for future rule-set expansion. */
  return 0;
}
