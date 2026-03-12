#include <stdio.h>
#include <string.h>

#include "internal/model.h"
#include "yai/container/mounts.h"

#define YAI_CONTAINER_MOUNT_FILE_MAX 128u

typedef struct {
  yai_container_mount_t entries[YAI_CONTAINER_MOUNT_FILE_MAX];
  size_t len;
} yai_container_mount_file_t;

static int mounts_file_path(const char *container_id, char *out, size_t out_cap) {
  char record_path[4096];
  char *slash;

  if (yai_container_model_record_path(container_id, record_path, sizeof(record_path)) != 0) {
    return -1;
  }

  slash = strrchr(record_path, '/');
  if (!slash) {
    return -1;
  }

  *slash = '\0';
  if (snprintf(out, out_cap, "%s/mounts.v1.bin", record_path) >= (int)out_cap) {
    return -1;
  }

  return 0;
}

int yai_container_mounts_add(const char *container_id,
                             const yai_container_mount_t *mount) {
  char path[4096];
  yai_container_mount_file_t file;
  FILE *fp;

  if (!container_id || !mount || container_id[0] == '\0' || mount->target[0] == '\0') {
    return -1;
  }

  if (!yai_container_model_exists(container_id)) {
    return -1;
  }

  memset(&file, 0, sizeof(file));
  if (mounts_file_path(container_id, path, sizeof(path)) != 0) {
    return -1;
  }

  fp = fopen(path, "rb");
  if (fp) {
    if (fread(&file, sizeof(file), 1, fp) != 1) {
      fclose(fp);
      return -1;
    }
    fclose(fp);
  }

  if (file.len >= YAI_CONTAINER_MOUNT_FILE_MAX) {
    return -1;
  }

  file.entries[file.len++] = *mount;

  fp = fopen(path, "wb");
  if (!fp) {
    return -1;
  }

  if (fwrite(&file, sizeof(file), 1, fp) != 1) {
    fclose(fp);
    return -1;
  }

  return fclose(fp) == 0 ? 0 : -1;
}
