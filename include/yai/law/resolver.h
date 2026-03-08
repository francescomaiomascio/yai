#pragma once

#include <stddef.h>

#include <yai/law/decision_map.h>
#include <yai/law/evidence_map.h>

typedef struct yai_law_resolution_output {
  yai_law_decision_t decision;
  yai_law_evidence_envelope_t evidence;
  char trace_json[2048];
} yai_law_resolution_output_t;

int yai_law_resolve_control_call(const char *ws_id,
                                 const char *payload,
                                 const char *trace_id,
                                 yai_law_resolution_output_t *out,
                                 char *err,
                                 size_t err_cap);
