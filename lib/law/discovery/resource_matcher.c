#include "../internal.h"

#include <string.h>

int yai_law_resource_match_bonus(const yai_law_classification_ctx_t *ctx, const char *domain_id, double *bonus) {
  if (!ctx || !domain_id || !bonus) return -1;
  *bonus = 0.0;
  if (strcmp(domain_id, "D1-digital") == 0 && strstr(ctx->resource, "external")) *bonus = 0.05;
  if (strcmp(domain_id, "D8-scientific") == 0 && (strstr(ctx->resource, "dataset") || strstr(ctx->resource, "experiment"))) *bonus = 0.05;
  return 0;
}
