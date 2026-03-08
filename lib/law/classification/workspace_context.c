#include "../internal.h"

#include <string.h>

int yai_law_extract_workspace_context(const char *payload,
                                      char *out_mode,
                                      size_t out_mode_cap,
                                      int *black_box_mode,
                                      int *has_params_hash,
                                      int *has_authority_contract) {
  if (!payload || !out_mode || !black_box_mode || !has_params_hash || !has_authority_contract) return -1;

  *black_box_mode = (strstr(payload, "black-box") || strstr(payload, "black_box")) ? 1 : 0;
  *has_params_hash = (strstr(payload, "params_hash") || strstr(payload, "param-lock")) ? 1 : 0;
  *has_authority_contract = (strstr(payload, "allowlist") || strstr(payload, "contract") || strstr(payload, "approved")) ? 1 : 0;

  if (*black_box_mode) return yai_law_safe_snprintf(out_mode, out_mode_cap, "%s", "black_box");
  return yai_law_safe_snprintf(out_mode, out_mode_cap, "%s", "default");
}
