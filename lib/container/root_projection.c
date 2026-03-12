#include <time.h>

#include <stdio.h>
#include <string.h>

#include "internal/model.h"

int yai_container_root_projection_initialize(const char *container_id) {
  yai_container_record_t record;
  int64_t now = (int64_t)time(NULL);

  if (!container_id || container_id[0] == '\0') {
    return -1;
  }

  if (yai_container_model_get(container_id, &record) != 0) {
    return -1;
  }

  record.root.projection_ready = 1;
  if (record.root.root_projection_handle == 0) {
    record.root.root_projection_handle = record.identity.state_handle;
  }
  if (record.root.mount_view_handle == 0) {
    record.root.mount_view_handle = record.identity.state_handle;
  }
  if (record.root.attach_view_handle == 0) {
    record.root.attach_view_handle = record.identity.state_handle;
  }
  if (record.root.root_path[0] == '\0') {
    (void)snprintf(record.root.root_path,
                   sizeof(record.root.root_path),
                   "/container/%s",
                   record.identity.container_id);
  }
  record.state.updated_at = now;

  return yai_container_model_upsert(&record);
}
