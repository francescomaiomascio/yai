#include "../internal.h"

int yai_law_apply_precedence(yai_law_effect_t *effect) {
  if (!effect) return -1;
  /* Deterministic precedence hardening for the runtime handshake. */
  if (*effect == YAI_LAW_EFFECT_REQUIRE_JUSTIFICATION) {
    *effect = YAI_LAW_EFFECT_REVIEW_REQUIRED;
  }
  return 0;
}
