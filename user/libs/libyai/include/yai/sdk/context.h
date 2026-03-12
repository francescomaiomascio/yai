/* SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Compatibility workspace-context API.
 * Canonical SDK-1 workspace taxonomy is declared in <yai/sdk/workspace.h>.
 */

/* Returns 0 and writes current ws_id when present.
 * Returns 1 when no current workspace is set.
 * Returns -1 on I/O/validation errors. */
int yai_sdk_context_get_current_workspace(char *out_ws_id, size_t out_cap);

/* Sets current workspace binding (canonical).
 * Returns 0 on success, -1 on validation/I/O errors. */
int yai_sdk_context_set_current_workspace(const char *ws_id);

/* Switches current workspace binding (compat/symmetry alias for set).
 * Returns 0 on success, -1 on validation/I/O errors. */
int yai_sdk_context_switch_workspace(const char *ws_id);

/* Unsets current workspace binding (canonical).
 * Returns 0 on success (also when already absent), -1 on I/O errors. */
int yai_sdk_context_unset_workspace(void);

/* Clears current workspace binding (compat alias for unset).
 * Returns 0 on success (also when already absent), -1 on I/O errors. */
int yai_sdk_context_clear_current_workspace(void);

/* Resolve effective workspace by precedence:
 * 1) explicit_ws_id when set
 * 2) current workspace context
 * Returns:
 * 0 -> resolved
 * 1 -> no workspace available
 * -1 -> errors */
int yai_sdk_context_resolve_workspace(
    const char *explicit_ws_id,
    char *out_ws_id,
    size_t out_cap);

typedef struct yai_sdk_workspace_info {
    char ws_id[64];
    int exists;
    int valid;
    char state[32];
    char root_path[512];
} yai_sdk_workspace_info_t;

/* Runtime-backed workspace descriptor using runtime workspace status command. */
int yai_sdk_workspace_describe(const char *ws_id, yai_sdk_workspace_info_t *out);

/* Validates current binding against runtime state.
 * Returns 0 when current binding exists and runtime confirms a valid workspace. */
int yai_sdk_context_validate_current_workspace(yai_sdk_workspace_info_t *out);

#ifdef __cplusplus
}
#endif
