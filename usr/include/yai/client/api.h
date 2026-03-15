/* SPDX-License-Identifier: Apache-2.0 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define YAI_SDK_ABI_VERSION 1

int yai_sdk_abi_version(void);
const char *yai_sdk_version(void);

/* Canonical unified-runtime public taxonomy. */
#include <yai/client/core.h>
#include <yai/client/runtime.h>
#include <yai/client/models.h>
#include <yai/client/targets.h>
#include <yai/client/transport.h>
#include <yai/client/container.h>
#include <yai/client/exec.h>
#include <yai/client/db.h>
#include <yai/client/data.h>
#include <yai/client/graph.h>
#include <yai/client/cognition.h>
#include <yai/client/source.h>
#include <yai/client/policy.h>
#include <yai/client/recovery.h>
#include <yai/client/debug.h>
#include <yai/client/governance.h>

/* Stable legacy module surface retained for compatibility. */
#include <yai/client/errors.h>
#include <yai/client/paths.h>
#include <yai/client/context.h>
#include <yai/client/client.h>
#include <yai/client/catalog.h>
#include <yai/client/protocol.h>
#include <yai/client/rpc.h>
#include <yai/client/log.h>
#include <yai/client/reply/reply.h>
#include <yai/client/reply/reply_builder.h>
#include <yai/client/reply/reply_json.h>

#ifdef __cplusplus
}
#endif
