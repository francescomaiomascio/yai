#ifndef YAI_KERNEL_KERNEL_H
#define YAI_KERNEL_KERNEL_H

#include <stdint.h>

void yai_kernel_bootstrap(uint64_t boot_id);
void yai_kernel_tick(void);

#endif /* YAI_KERNEL_KERNEL_H */
