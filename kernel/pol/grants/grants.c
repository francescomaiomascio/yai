/* SPDX-License-Identifier: Apache-2.0 */
#include <yai/pol/grants.h>

#include "yai/abi/errors.h"
#include "yai/kernel/grants.h"
#include "yai/kernel/lifecycle.h"
#include "yai/kernel/registry.h"

#include <stdio.h>
#include <string.h>

int yai_policy_grants_view_json(const char *scope_id, char *out, size_t out_cap)
{
    if (!out || out_cap == 0) return -1;
    if (!scope_id || !scope_id[0]) scope_id = "user";
    return (snprintf(out, out_cap, "{\"scope\":\"%s\",\"grants_state\":\"active\"}", scope_id) < (int)out_cap)
               ? 0
               : -1;
}

int yai_kernel_grant_transition_allowed(
    enum yai_kernel_grant_state from,
    enum yai_kernel_grant_state to)
{
    switch (from) {
        case YAI_KERNEL_GRANT_PENDING:
            return (to == YAI_KERNEL_GRANT_ACTIVE ||
                    to == YAI_KERNEL_GRANT_DENIED ||
                    to == YAI_KERNEL_GRANT_REVOKED) ? YAI_OK : YAI_ERR_DENIED;
        case YAI_KERNEL_GRANT_ACTIVE:
            return (to == YAI_KERNEL_GRANT_SUSPENDED ||
                    to == YAI_KERNEL_GRANT_REVOKED ||
                    to == YAI_KERNEL_GRANT_EXPIRED) ? YAI_OK : YAI_ERR_DENIED;
        case YAI_KERNEL_GRANT_SUSPENDED:
            return (to == YAI_KERNEL_GRANT_ACTIVE ||
                    to == YAI_KERNEL_GRANT_REVOKED ||
                    to == YAI_KERNEL_GRANT_EXPIRED) ? YAI_OK : YAI_ERR_DENIED;
        case YAI_KERNEL_GRANT_DENIED:
        case YAI_KERNEL_GRANT_REVOKED:
        case YAI_KERNEL_GRANT_EXPIRED:
            return YAI_ERR_DENIED;
        default:
            return YAI_ERR_INVALID;
    }
}

int yai_kernel_grant_set_state(struct yai_kernel_grant *grant,
                               enum yai_kernel_grant_state state)
{
    int rc;

    if (grant == 0) return YAI_ERR_INVALID;

    rc = yai_kernel_grant_transition_allowed(grant->validity_state, state);
    if (rc != YAI_OK) return rc;

    grant->validity_state = state;
    return YAI_OK;
}

int yai_kernel_grant_check(
    yai_object_id_t subject_handle,
    enum yai_kernel_capability_class capability_class,
    yai_object_id_t scope_handle,
    struct yai_kernel_grant *out_grant)
{
    int rc;

    if (out_grant == 0) return YAI_ERR_INVALID;

    rc = yai_grants_registry_find_active(subject_handle, capability_class, scope_handle, out_grant);
    if (rc != YAI_OK) return rc;

    if (out_grant->validity_state != YAI_KERNEL_GRANT_ACTIVE) {
        return YAI_ERR_DENIED;
    }

    return YAI_OK;
}

int yai_kernel_grant_issue(const struct yai_kernel_grant_request *request,
                           struct yai_kernel_grant *out_grant)
{
    struct yai_kernel_grant grant;
    int rc;

    if (request == 0 || out_grant == 0 || request->grant_id == 0 || request->subject_handle == 0) {
        return YAI_ERR_INVALID;
    }

    rc = yai_kernel_can_issue_grants();
    if (rc != YAI_OK) return rc;

    memset(&grant, 0, sizeof(grant));
    grant.grant_id = request->grant_id;
    grant.subject_handle = request->subject_handle;
    grant.capability_class = request->capability_class;
    grant.scope_handle = request->scope_handle;
    grant.validity_state = YAI_KERNEL_GRANT_PENDING;
    grant.issued_at = request->issued_at;
    grant.expires_at = request->expires_at;
    grant.revoked_at = 0;
    grant.flags = request->flags;

    rc = yai_grants_registry_set(&grant);
    if (rc != YAI_OK) return rc;

    *out_grant = grant;
    return YAI_OK;
}

int yai_kernel_grant_activate(yai_object_id_t grant_id)
{
    struct yai_kernel_grant grant;
    int rc = yai_grants_registry_get(grant_id, &grant);
    if (rc != YAI_OK) return rc;

    rc = yai_kernel_grant_set_state(&grant, YAI_KERNEL_GRANT_ACTIVE);
    if (rc != YAI_OK) return rc;

    return yai_grants_registry_set(&grant);
}

int yai_kernel_grant_suspend(yai_object_id_t grant_id, uint64_t flags)
{
    struct yai_kernel_grant grant;
    int rc = yai_grants_registry_get(grant_id, &grant);
    if (rc != YAI_OK) return rc;

    rc = yai_kernel_grant_set_state(&grant, YAI_KERNEL_GRANT_SUSPENDED);
    if (rc != YAI_OK) return rc;

    grant.flags |= flags;
    return yai_grants_registry_set(&grant);
}

int yai_kernel_grant_revoke(yai_object_id_t grant_id, uint64_t revoked_at, uint64_t flags)
{
    struct yai_kernel_grant grant;
    int rc = yai_grants_registry_get(grant_id, &grant);
    if (rc != YAI_OK) return rc;

    rc = yai_kernel_grant_set_state(&grant, YAI_KERNEL_GRANT_REVOKED);
    if (rc != YAI_OK) return rc;

    grant.revoked_at = revoked_at;
    grant.flags |= flags;
    return yai_grants_registry_set(&grant);
}

int yai_kernel_grant_expire(yai_object_id_t grant_id, uint64_t expired_at)
{
    struct yai_kernel_grant grant;
    int rc = yai_grants_registry_get(grant_id, &grant);
    if (rc != YAI_OK) return rc;

    rc = yai_kernel_grant_set_state(&grant, YAI_KERNEL_GRANT_EXPIRED);
    if (rc != YAI_OK) return rc;

    grant.expires_at = expired_at;
    return yai_grants_registry_set(&grant);
}
