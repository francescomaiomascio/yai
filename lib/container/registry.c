#include <string.h>

#include "internal/model.h"

int yai_container_register(const yai_container_record_t *record) {
  if (!record || record->identity.container_id[0] == '\0') {
    return -1;
  }

  if (yai_container_model_exists(record->identity.container_id)) {
    return -1;
  }

  return yai_container_model_upsert(record);
}

int yai_container_get(const char *container_id, yai_container_record_t *out_record) {
  return yai_container_model_get(container_id, out_record);
}

int yai_container_set_lifecycle(const char *container_id,
                                yai_container_lifecycle_state_t next_state,
                                int64_t at) {
  yai_container_record_t record;

  if (yai_container_model_get(container_id, &record) != 0) {
    return -1;
  }

  if (!yai_container_lifecycle_transition_allowed(record.lifecycle.current, next_state)) {
    return -1;
  }

  record.lifecycle.previous = record.lifecycle.current;
  record.lifecycle.current = next_state;
  record.lifecycle.updated_at = at;
  record.state.lifecycle_state = next_state;
  record.state.updated_at = at;

  if (next_state == YAI_CONTAINER_LIFECYCLE_SEALED) {
    record.lifecycle.sealed_at = at;
  }
  if (next_state == YAI_CONTAINER_LIFECYCLE_DESTROYED) {
    record.lifecycle.destroyed_at = at;
  }

  return yai_container_model_upsert(&record);
}
