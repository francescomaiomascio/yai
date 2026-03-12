#pragma once

#include <stdint.h>

#define YAI_CONTAINER_PATH_MAX 511u

typedef struct {
  uint64_t container_root_handle;
  uint64_t root_projection_handle;
  uint64_t mount_view_handle;
  uint64_t attach_view_handle;
  uint8_t projection_ready;
  char root_path[YAI_CONTAINER_PATH_MAX + 1u];
} yai_container_root_t;
