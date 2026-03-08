#include "../internal.h"

#include <string.h>

int yai_law_match_signal_score(const yai_law_classification_ctx_t *ctx,
                               const char *domain_id,
                               double *score,
                               char *rationale,
                               size_t rationale_cap) {
  double s = 0.0;
  if (!ctx || !domain_id || !score) return -1;

  if (strcmp(domain_id, "D1-digital") == 0) {
    if (strcmp(ctx->action, "egress") == 0 || strcmp(ctx->action, "publish") == 0) s += 0.40;
    if (strstr(ctx->provider, "curl") || strstr(ctx->provider, "otel") || strstr(ctx->provider, "s3") || strstr(ctx->provider, "github")) s += 0.35;
    if (strstr(ctx->resource, "external") || strstr(ctx->resource, "bucket")) s += 0.25;
    if (rationale) (void)yai_law_safe_snprintf(rationale, rationale_cap, "%s", "digital egress/publication signal match");
  } else if (strcmp(domain_id, "D8-scientific") == 0) {
    if (strstr(ctx->action, "experiment") || strstr(ctx->action, "parameter") || strcmp(ctx->action, "infer") == 0) s += 0.40;
    if (strstr(ctx->provider, "experiment") || strstr(ctx->resource, "dataset") || strstr(ctx->resource, "experiment")) s += 0.35;
    if (ctx->has_params_hash || ctx->black_box_mode) s += 0.25;
    if (rationale) (void)yai_law_safe_snprintf(rationale, rationale_cap, "%s", "scientific reproducibility signal match");
  } else {
    s = 0.10;
    if (rationale) (void)yai_law_safe_snprintf(rationale, rationale_cap, "%s", "fallback low-confidence match");
  }

  *score = s;
  return 0;
}
