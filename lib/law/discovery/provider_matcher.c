#include "../internal.h"

int yai_law_provider_match_bonus(const yai_law_classification_ctx_t *ctx, const char *domain_id, double *bonus) {
  if (!ctx || !domain_id || !bonus) return -1;
  *bonus = 0.0;
  if (domain_id[1] == '1' && ctx->provider[0] != '\0') *bonus = 0.05;
  if (domain_id[1] == '8' && ctx->provider[0] != '\0') *bonus = 0.05;
  return 0;
}
