#include "../internal.h"

int yai_law_protocol_match_bonus(const yai_law_classification_ctx_t *ctx, const char *domain_id, double *bonus) {
  if (!ctx || !domain_id || !bonus) return -1;
  *bonus = 0.0;
  if (domain_id[1] == '1' && (ctx->protocol[0] == 'h' || ctx->protocol[0] == 'g')) *bonus = 0.05;
  if (domain_id[1] == '8' && ctx->protocol[0] == 'c') *bonus = 0.05;
  return 0;
}
