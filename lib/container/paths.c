#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "yai/container/paths.h"

int yai_container_paths_join(const char *root,
                             const char *relative,
                             char *out,
                             size_t out_cap) {
  int n;

  if (!root || !relative || !out || out_cap == 0) {
    return -1;
  }

  n = snprintf(out, out_cap, "%s/%s", root, relative);
  if (n < 0 || (size_t)n >= out_cap) {
    return -1;
  }

  return 0;
}
