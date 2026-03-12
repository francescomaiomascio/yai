#ifndef YAI_CONTAINER_MOUNTS_H
#define YAI_CONTAINER_MOUNTS_H

#include <stdint.h>
#include "yai/kernel/handles.h"

enum yai_mount_policy_class {
    YAI_MOUNT_POLICY_READONLY = 0,
    YAI_MOUNT_POLICY_SCOPED_RW = 1,
    YAI_MOUNT_POLICY_PRIVILEGED_RW = 2
};

int yai_kernel_mounts_validate_policy(enum yai_mount_policy_class mount_policy, uint64_t flags);

#endif /* YAI_CONTAINER_MOUNTS_H */
