#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>

#include "internal/model.h"
#include "yai/container/services.h"

#define YAI_CONTAINER_SERVICE_MAX 64u

typedef struct {
  yai_container_service_entry_t entries[YAI_CONTAINER_SERVICE_MAX];
  size_t len;
} yai_container_services_file_t;

static int services_file_path(const char *container_id, char *out, size_t out_cap) {
  char record_path[4096];
  char *slash = NULL;

  if (yai_container_model_record_path(container_id, record_path, sizeof(record_path)) != 0) {
    return -1;
  }

  slash = strrchr(record_path, '/');
  if (!slash) {
    return -1;
  }

  *slash = '\0';
  if (snprintf(out, out_cap, "%s/services.v1.bin", record_path) >= (int)out_cap) {
    return -1;
  }

  return 0;
}

static int services_load(const char *container_id, yai_container_services_file_t *file) {
  char path[4096];
  FILE *fp;

  if (!file) {
    return -1;
  }
  memset(file, 0, sizeof(*file));

  if (services_file_path(container_id, path, sizeof(path)) != 0) {
    return -1;
  }

  fp = fopen(path, "rb");
  if (!fp) {
    return 0;
  }

  if (fread(file, sizeof(*file), 1, fp) != 1) {
    fclose(fp);
    return -1;
  }
  fclose(fp);

  if (file->len > YAI_CONTAINER_SERVICE_MAX) {
    file->len = YAI_CONTAINER_SERVICE_MAX;
  }

  return 0;
}

static int services_save(const char *container_id, const yai_container_services_file_t *file) {
  char path[4096];
  FILE *fp;

  if (!file) {
    return -1;
  }

  if (services_file_path(container_id, path, sizeof(path)) != 0) {
    return -1;
  }

  fp = fopen(path, "wb");
  if (!fp) {
    return -1;
  }

  if (fwrite(file, sizeof(*file), 1, fp) != 1) {
    fclose(fp);
    return -1;
  }

  return fclose(fp) == 0 ? 0 : -1;
}

int yai_container_services_upsert(const char *container_id,
                                  const yai_container_service_entry_t *entry) {
  yai_container_services_file_t file;
  size_t i;

  if (!container_id || !entry || container_id[0] == '\0' || entry->name[0] == '\0') {
    return -1;
  }

  if (!yai_container_model_exists(container_id)) {
    return -1;
  }

  if (services_load(container_id, &file) != 0) {
    return -1;
  }

  for (i = 0; i < file.len; ++i) {
    if (strncmp(file.entries[i].name, entry->name, YAI_CONTAINER_SERVICE_NAME_MAX) == 0) {
      file.entries[i] = *entry;
      return services_save(container_id, &file);
    }
  }

  if (file.len >= YAI_CONTAINER_SERVICE_MAX) {
    return -1;
  }

  file.entries[file.len++] = *entry;
  return services_save(container_id, &file);
}

int yai_container_services_list(const char *container_id,
                                yai_container_service_entry_t *entries,
                                size_t cap,
                                size_t *out_len) {
  yai_container_services_file_t file;
  size_t i;

  if (!container_id || !entries || !out_len) {
    return -1;
  }

  if (!yai_container_model_exists(container_id)) {
    return -1;
  }

  if (services_load(container_id, &file) != 0) {
    return -1;
  }

  *out_len = (file.len < cap) ? file.len : cap;
  for (i = 0; i < *out_len; ++i) {
    entries[i] = file.entries[i];
  }
  return 0;
}
