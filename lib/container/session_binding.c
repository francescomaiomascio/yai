#include <time.h>

#include "internal/model.h"
#include "yai/container/registry.h"

int yai_container_session_bind(const char *container_id, uint64_t session_id) {
  yai_container_record_t record;
  int64_t now = (int64_t)time(NULL);

  if (!container_id || container_id[0] == '\0' || session_id == 0) {
    return -1;
  }

  if (yai_container_model_get(container_id, &record) != 0) {
    return -1;
  }

  record.session_domain.bound = 1;
  record.session_domain.bound_session_count += 1;
  record.session_domain.last_bound_session_id = session_id;
  record.session_domain.last_bound_at = (uint64_t)now;
  record.state.updated_at = now;

  if (record.lifecycle.current == YAI_CONTAINER_LIFECYCLE_OPEN ||
      record.lifecycle.current == YAI_CONTAINER_LIFECYCLE_INITIALIZED) {
    if (yai_container_set_lifecycle(container_id, YAI_CONTAINER_LIFECYCLE_ACTIVE, now) != 0) {
      return -1;
    }
    if (yai_container_model_get(container_id, &record) != 0) {
      return -1;
    }
    record.session_domain.bound = 1;
    record.session_domain.bound_session_count += 1;
    record.session_domain.last_bound_session_id = session_id;
    record.session_domain.last_bound_at = (uint64_t)now;
    record.state.updated_at = now;
  }

  return yai_container_model_upsert(&record);
}
