#include "yai/kernel/kernel.h"

void yai_kernel_init_early(void) {
    yai_kernel_bootstrap(1u);
}
