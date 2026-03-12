#include <string.h>

#include "yai/container/tree.h"

void yai_container_tree_defaults(yai_container_tree_t *tree) {
  if (!tree) {
    return;
  }
  memset(tree, 0, sizeof(*tree));
}
