#include <time.h>

#include "internal/model.h"
#include "yai/container/recovery.h"
#include "yai/container/registry.h"

int yai_container_enter_recovery(const char *container_id, uint64_t reason_flags) {
  yai_container_record_t record;
  int64_t now = (int64_t)time(NULL);

  if (!container_id || container_id[0] == '\0') {
    return -1;
  }

  if (yai_container_get(container_id, &record) != 0) {
    return -1;
  }

  record.state.recovery_reason_flags = reason_flags;
  record.state.updated_at = now;

  if (record.lifecycle.current == YAI_CONTAINER_LIFECYCLE_ACTIVE ||
      record.lifecycle.current == YAI_CONTAINER_LIFECYCLE_OPEN ||
      record.lifecycle.current == YAI_CONTAINER_LIFECYCLE_INITIALIZED) {
    if (yai_container_set_lifecycle(container_id, YAI_CONTAINER_LIFECYCLE_DEGRADED, now) != 0) {
      return -1;
    }
  }

  if (yai_container_set_lifecycle(container_id, YAI_CONTAINER_LIFECYCLE_RECOVERY, now) != 0) {
    return -1;
  }

  if (yai_container_get(container_id, &record) != 0) {
    return -1;
  }
  record.state.recovery_reason_flags = reason_flags;
  record.state.updated_at = now;
  return yai_container_model_upsert(&record);
}

int yai_container_seal(const char *container_id, int64_t sealed_at) {
  return yai_container_set_lifecycle(container_id, YAI_CONTAINER_LIFECYCLE_SEALED, sealed_at);
}

int yai_container_restore(const char *container_id) {
  yai_container_record_t record;
  int64_t now = (int64_t)time(NULL);

  if (!container_id || container_id[0] == '\0') {
    return -1;
  }

  if (yai_container_get(container_id, &record) != 0) {
    return -1;
  }

  if (yai_container_set_lifecycle(container_id, YAI_CONTAINER_LIFECYCLE_ACTIVE, now) != 0) {
    return -1;
  }

  if (yai_container_get(container_id, &record) != 0) {
    return -1;
  }
  record.state.recovery_reason_flags = 0;
  record.state.updated_at = now;
  return yai_container_model_upsert(&record);
}
