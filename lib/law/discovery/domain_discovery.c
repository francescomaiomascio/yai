#include <yai/law/discovery.h>

#include "../internal.h"

#include <string.h>

int yai_law_protocol_match_bonus(const yai_law_classification_ctx_t *ctx, const char *domain_id, double *bonus);
int yai_law_provider_match_bonus(const yai_law_classification_ctx_t *ctx, const char *domain_id, double *bonus);
int yai_law_resource_match_bonus(const yai_law_classification_ctx_t *ctx, const char *domain_id, double *bonus);
int yai_law_command_match_bonus(const yai_law_classification_ctx_t *ctx, const char *domain_id, double *bonus);
int yai_law_confidence_label(double score, int *ambiguous);

int yai_law_discover_domain(const yai_law_classification_ctx_t *ctx,
                            yai_law_discovery_result_t *out) {
  double d1 = 0.0, d8 = 0.0;
  double b = 0.0;
  char r1[128] = {0};
  char r8[128] = {0};

  if (!ctx || !out) return -1;
  memset(out, 0, sizeof(*out));

  (void)yai_law_match_signal_score(ctx, "D1-digital", &d1, r1, sizeof(r1));
  (void)yai_law_protocol_match_bonus(ctx, "D1-digital", &b); d1 += b;
  (void)yai_law_provider_match_bonus(ctx, "D1-digital", &b); d1 += b;
  (void)yai_law_resource_match_bonus(ctx, "D1-digital", &b); d1 += b;
  (void)yai_law_command_match_bonus(ctx, "D1-digital", &b); d1 += b;

  (void)yai_law_match_signal_score(ctx, "D8-scientific", &d8, r8, sizeof(r8));
  (void)yai_law_protocol_match_bonus(ctx, "D8-scientific", &b); d8 += b;
  (void)yai_law_provider_match_bonus(ctx, "D8-scientific", &b); d8 += b;
  (void)yai_law_resource_match_bonus(ctx, "D8-scientific", &b); d8 += b;
  (void)yai_law_command_match_bonus(ctx, "D8-scientific", &b); d8 += b;

  if (d8 > d1) {
    (void)yai_law_safe_snprintf(out->domain_id, sizeof(out->domain_id), "%s", "D8-scientific");
    out->confidence = d8;
    (void)yai_law_safe_snprintf(out->rationale, sizeof(out->rationale), "%s", r8);
  } else {
    (void)yai_law_safe_snprintf(out->domain_id, sizeof(out->domain_id), "%s", "D1-digital");
    out->confidence = d1;
    (void)yai_law_safe_snprintf(out->rationale, sizeof(out->rationale), "%s", r1);
  }

  (void)yai_law_confidence_label(out->confidence, &out->ambiguous);
  if (out->confidence < 0.45) {
    (void)yai_law_safe_snprintf(out->domain_id, sizeof(out->domain_id), "%s", "D1-digital");
    out->ambiguous = 1;
    (void)yai_law_safe_snprintf(out->rationale, sizeof(out->rationale), "%s", "low confidence fallback to D1-digital");
  }

  return 0;
}
