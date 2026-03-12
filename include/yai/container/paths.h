#pragma once

#include <stddef.h>

int yai_container_paths_join(const char *root,
                             const char *relative,
                             char *out,
                             size_t out_cap);
