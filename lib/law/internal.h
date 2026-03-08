#pragma once

#include <stddef.h>

#include <yai/law/classifier.h>
#include <yai/law/decision_map.h>
#include <yai/law/discovery.h>
#include <yai/law/loader.h>

int yai_law_read_text_file(const char *path, char *out, size_t out_cap);
int yai_law_json_extract_string(const char *json, const char *key, char *out, size_t out_cap);
int yai_law_json_contains(const char *json, const char *needle);
int yai_law_safe_snprintf(char *out, size_t out_cap, const char *fmt, ...);

int yai_law_classify_action(const char *payload, char *out, size_t out_cap);
int yai_law_classify_provider(const char *payload, char *out, size_t out_cap);
int yai_law_classify_resource(const char *payload, char *out, size_t out_cap);
int yai_law_classify_protocol(const char *payload, char *out, size_t out_cap);
int yai_law_extract_workspace_context(const char *payload, char *out_mode, size_t out_mode_cap,
                                      int *black_box_mode, int *has_params_hash, int *has_authority_contract);

int yai_law_match_signal_score(const yai_law_classification_ctx_t *ctx,
                               const char *domain_id,
                               double *score,
                               char *rationale,
                               size_t rationale_cap);

int yai_law_stack_build(const yai_law_runtime_t *rt,
                        const yai_law_discovery_result_t *discovery,
                        const yai_law_classification_ctx_t *ctx,
                        yai_law_effective_stack_t *stack,
                        yai_law_effect_t *effect,
                        char *rationale,
                        size_t rationale_cap);

int yai_law_build_trace_json(const yai_law_classification_ctx_t *ctx,
                             const yai_law_discovery_result_t *disc,
                             const yai_law_decision_t *decision,
                             char *out,
                             size_t out_cap);
