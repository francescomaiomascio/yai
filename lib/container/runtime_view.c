#include <string.h>

#include "internal/model.h"
#include "yai/container/runtime_view.h"

int yai_container_runtime_view_get(const char *container_id,
                                   yai_container_runtime_view_t *out_view) {
  yai_container_record_t record;

  if (!container_id || !out_view || container_id[0] == '\0') {
    return -1;
  }

  if (yai_container_model_get(container_id, &record) != 0) {
    return -1;
  }

  memset(out_view, 0, sizeof(*out_view));
  out_view->state = record.state;

  if (yai_container_policy_view_get(container_id, &out_view->policy_view) != 0) {
    return -1;
  }
  if (yai_container_grants_view_get(container_id, &out_view->grants_view) != 0) {
    return -1;
  }

  out_view->bindings.daemon_binding_handle = record.state.daemon_bindings;
  out_view->bindings.network_binding_handle = record.state.network_bindings;
  out_view->bindings.orchestration_binding_handle = record.state.attachments;
  return 0;
}
