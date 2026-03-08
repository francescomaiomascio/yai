#pragma once

#include <yai/law/decision_map.h>

typedef struct yai_law_evidence_envelope {
  char trace_id[64];
  char decision_id[64];
  char domain_id[64];
  char final_effect[32];
  char provider[64];
  char resource[64];
  char authority_context[64];
} yai_law_evidence_envelope_t;

int yai_law_decision_to_evidence(const yai_law_decision_t *decision,
                                 const char *trace_id,
                                 const char *provider,
                                 const char *resource,
                                 const char *authority_context,
                                 yai_law_evidence_envelope_t *out);
