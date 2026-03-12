#pragma once

#include <stdint.h>

typedef struct {
  uint64_t tree_handle;
  uint64_t node_count;
  uint64_t leaf_count;
} yai_container_tree_t;

void yai_container_tree_defaults(yai_container_tree_t *tree);
