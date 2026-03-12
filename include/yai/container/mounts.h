#pragma once

#include <stddef.h>
#include <stdint.h>

#define YAI_CONTAINER_MOUNT_MAX 127u
#define YAI_CONTAINER_MOUNT_PATH_MAX 255u

typedef enum {
  YAI_CONTAINER_MOUNT_RO = 0,
  YAI_CONTAINER_MOUNT_RW,
  YAI_CONTAINER_MOUNT_PRIVILEGED,
} yai_container_mount_policy_t;

typedef struct {
  char source[YAI_CONTAINER_MOUNT_PATH_MAX + 1u];
  char target[YAI_CONTAINER_MOUNT_PATH_MAX + 1u];
  yai_container_mount_policy_t policy;
} yai_container_mount_t;

int yai_container_mounts_add(const char *container_id,
                             const yai_container_mount_t *mount);
