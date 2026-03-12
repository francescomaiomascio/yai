/* SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include <yai/sdk/client.h>

#ifdef __cplusplus
extern "C" {
#endif

int yai_cli_lifecycle_run(const char *command_id, yai_sdk_reply_t *out);

#ifdef __cplusplus
}
#endif

