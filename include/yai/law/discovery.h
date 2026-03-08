#pragma once

#include <yai/law/classifier.h>

typedef struct yai_law_discovery_result {
  char domain_id[64];
  double confidence;
  int ambiguous;
  char rationale[192];
} yai_law_discovery_result_t;

int yai_law_discover_domain(const yai_law_classification_ctx_t *ctx,
                            yai_law_discovery_result_t *out);
