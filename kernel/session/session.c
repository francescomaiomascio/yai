#include <string.h>

#include "yai/abi/errors.h"
#include "yai/kernel/lifecycle.h"
#include "yai/kernel/policy.h"
#include "yai/kernel/registry.h"
#include "yai/kernel/session.h"
#include "yai/kernel/state.h"

static int yai_kernel_session_store(const struct yai_kernel_session *session)
{
    return yai_session_registry_upsert(session);
}

static int yai_kernel_session_load(yai_object_id_t session_id,
                                   struct yai_kernel_session *out_session)
{
    return yai_session_registry_get(session_id, out_session);
}

int yai_kernel_session_get(yai_object_id_t session_id,
                           struct yai_kernel_session *out_session)
{
    return yai_kernel_session_load(session_id, out_session);
}

int yai_kernel_session_admit(
    yai_object_id_t session_id,
    const struct yai_kernel_session_request *request,
    struct yai_kernel_session *out_session)
{
    struct yai_kernel_session session;
    struct yai_kernel_session existing;
    enum yai_kernel_policy_result policy_result;
    int rc;

    if (session_id == 0 || request == 0 || out_session == 0) {
        return YAI_ERR_INVALID;
    }

    rc = yai_kernel_can_admit_sessions();
    if (rc != YAI_OK) return rc;

    rc = yai_kernel_session_load(session_id, &existing);
    if (rc == YAI_OK) return YAI_ERR_BUSY;

    rc = yai_kernel_policy_can_admit_session(session_id, request, &policy_result);
    if (rc != YAI_OK) return rc;
    if (policy_result != YAI_KERNEL_POLICY_ALLOW) return YAI_ERR_DENIED;

    memset(&session, 0, sizeof(session));
    session.session_id = session_id;
    session.session_type = request->requested_type;
    session.privilege_class = request->requested_privilege_class;
    session.admission_source = request->admission_source;
    session.admission_state = YAI_KERNEL_SESSION_ADMITTED;
    session.bound_container_id = 0;
    session.capability_mask = request->capability_mask;
    session.created_at = request->created_at;
    session.revoked_at = 0;
    session.flags = request->flags;

    rc = yai_kernel_session_store(&session);
    if (rc != YAI_OK) return rc;

    yai_kernel_state_inc_sessions();
    *out_session = session;
    return YAI_OK;
}

int yai_kernel_session_bind_container(yai_object_id_t session_id,
                                      yai_object_id_t container_id)
{
    struct yai_kernel_session session;
    enum yai_kernel_policy_result policy_result;
    int rc;

    if (session_id == 0 || container_id == 0) return YAI_ERR_INVALID;

    rc = yai_kernel_can_bind_container();
    if (rc != YAI_OK) return rc;

    rc = yai_kernel_session_load(session_id, &session);
    if (rc != YAI_OK) return rc;

    if (session.admission_state != YAI_KERNEL_SESSION_ADMITTED) {
        return YAI_ERR_DENIED;
    }

    rc = yai_kernel_policy_can_bind_container(session.session_id,
                                              session_id,
                                              container_id,
                                              &policy_result);
    if (rc != YAI_OK) return rc;
    if (policy_result != YAI_KERNEL_POLICY_ALLOW) return YAI_ERR_DENIED;

    session.bound_container_id = container_id;
    session.session_type = YAI_KERNEL_SESSION_CONTAINER_BOUND;
    session.admission_state = YAI_KERNEL_SESSION_BOUND;

    return yai_kernel_session_store(&session);
}

int yai_kernel_session_suspend(yai_object_id_t session_id, uint64_t flags)
{
    struct yai_kernel_session session;
    int rc;

    if (session_id == 0) return YAI_ERR_INVALID;

    rc = yai_kernel_session_load(session_id, &session);
    if (rc != YAI_OK) return rc;

    if (session.admission_state != YAI_KERNEL_SESSION_ADMITTED &&
        session.admission_state != YAI_KERNEL_SESSION_BOUND) {
        return YAI_ERR_DENIED;
    }

    session.admission_state = YAI_KERNEL_SESSION_SUSPENDED;
    session.flags |= flags;
    return yai_kernel_session_store(&session);
}

int yai_kernel_session_revoke(yai_object_id_t session_id,
                              uint64_t revoked_at,
                              uint64_t flags)
{
    struct yai_kernel_session session;
    int rc;

    if (session_id == 0) return YAI_ERR_INVALID;

    rc = yai_kernel_session_load(session_id, &session);
    if (rc != YAI_OK) return rc;

    if (session.admission_state == YAI_KERNEL_SESSION_CLOSED) {
        return YAI_ERR_DENIED;
    }

    session.admission_state = YAI_KERNEL_SESSION_REVOKED;
    session.revoked_at = revoked_at;
    session.flags |= flags;
    return yai_kernel_session_store(&session);
}

int yai_kernel_session_close(yai_object_id_t session_id)
{
    struct yai_kernel_session session;
    int rc;

    if (session_id == 0) return YAI_ERR_INVALID;

    rc = yai_kernel_session_load(session_id, &session);
    if (rc != YAI_OK) return rc;

    session.admission_state = YAI_KERNEL_SESSION_CLOSED;
    return yai_kernel_session_store(&session);
}
