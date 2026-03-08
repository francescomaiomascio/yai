#include "../internal.h"

#include <string.h>

int yai_law_command_match_bonus(const yai_law_classification_ctx_t *ctx, const char *domain_id, double *bonus) {
  if (!ctx || !domain_id || !bonus) return -1;
  *bonus = 0.0;
  if (strcmp(domain_id, "D1-digital") == 0 && (strstr(ctx->command, "curl") || strstr(ctx->command, "s3") || strstr(ctx->command, "github"))) *bonus = 0.05;
  if (strcmp(domain_id, "D8-scientific") == 0 && strstr(ctx->command, "experiment")) *bonus = 0.05;
  return 0;
}
