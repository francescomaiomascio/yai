#include "../internal.h"

int yai_law_resolve_conflicts(yai_governance_effect_t *effect) {
  if (!effect) return -1;
  /* Deterministic MVP: no multi-rule conflicts yet beyond precedence table. */
  return 0;
}
