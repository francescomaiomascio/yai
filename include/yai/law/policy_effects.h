#pragma once

typedef enum yai_law_effect {
  YAI_LAW_EFFECT_ALLOW = 0,
  YAI_LAW_EFFECT_DENY,
  YAI_LAW_EFFECT_QUARANTINE,
  YAI_LAW_EFFECT_REVIEW_REQUIRED,
  YAI_LAW_EFFECT_DEGRADE,
  YAI_LAW_EFFECT_REQUIRE_JUSTIFICATION,
  YAI_LAW_EFFECT_UNKNOWN
} yai_law_effect_t;

const char *yai_law_effect_name(yai_law_effect_t effect);
