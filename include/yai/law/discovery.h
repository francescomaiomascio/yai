#pragma once

#include <yai/law/classifier.h>

typedef struct yai_law_discovery_result {
  char domain_id[64];
  char family_id[64];
  char specialization_id[96];
  char family_candidates[4][64];
  double family_candidate_scores[4];
  int family_candidate_count;
  char specialization_candidates[6][96];
  int specialization_candidate_count;
  double confidence;
  int ambiguous;
  char rationale[192];
} yai_law_discovery_result_t;

int yai_law_discover_domain(const yai_law_classification_ctx_t *ctx,
                            yai_law_discovery_result_t *out);
