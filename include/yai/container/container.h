#pragma once

#include "bindings.h"
#include "config.h"
#include "grants_view.h"
#include "identity.h"
#include "lifecycle.h"
#include "mounts.h"
#include "paths.h"
#include "policy_view.h"
#include "recovery.h"
#include "registry.h"
#include "root.h"
#include "runtime_view.h"
#include "services.h"
#include "session.h"
#include "state.h"
#include "tree.h"

/* Container manager primitives (canonical runtime surface). */
int yai_container_create(const yai_container_record_t *record);
int yai_container_open(const char *container_id);
int yai_container_attach(const char *container_id, uint64_t session_id);
int yai_container_initialize(const char *container_id);
int yai_container_recover(const char *container_id, uint64_t reason_flags);
int yai_container_seal_runtime(const char *container_id, int64_t sealed_at);
int yai_container_destroy(const char *container_id, int64_t destroyed_at);

/* Container runtime surface primitives. */
int yai_container_get_identity(const char *container_id, yai_container_identity_t *out_identity);
int yai_container_get_state(const char *container_id, yai_container_state_t *out_state);
int yai_container_get_root_view(const char *container_id, yai_container_root_t *out_root);
int yai_container_get_session_view(const char *container_id, yai_container_session_domain_t *out_session);
int yai_container_get_policy_view(const char *container_id, yai_container_policy_view_t *out_view);
int yai_container_get_grants_view(const char *container_id, yai_container_grants_view_t *out_view);
int yai_container_get_runtime_view(const char *container_id, yai_container_runtime_view_t *out_view);
