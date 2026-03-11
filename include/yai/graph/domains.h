/* SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int yai_graph_domain_activation_summary_json(const char *workspace_id,
                                             char *out_json,
                                             size_t out_cap,
                                             char *err,
                                             size_t err_cap);
int yai_graph_domain_authority_summary_json(const char *workspace_id,
                                            char *out_json,
                                            size_t out_cap,
                                            char *err,
                                            size_t err_cap);
int yai_graph_domain_episodic_summary_json(const char *workspace_id,
                                           char *out_json,
                                           size_t out_cap,
                                           char *err,
                                           size_t err_cap);
int yai_graph_domain_semantic_summary_json(const char *workspace_id,
                                           char *out_json,
                                           size_t out_cap,
                                           char *err,
                                           size_t err_cap);

#ifdef __cplusplus
}
#endif
