#pragma once

#include <stddef.h>
#include <stdint.h>

#include "identity.h"

#define YAI_CONTAINER_SERVICE_NAME_MAX 63u

typedef struct {
  char name[YAI_CONTAINER_SERVICE_NAME_MAX + 1u];
  uint64_t service_handle;
  uint8_t active;
} yai_container_service_entry_t;

int yai_container_services_upsert(const char *container_id,
                                  const yai_container_service_entry_t *entry);
int yai_container_services_list(const char *container_id,
                                yai_container_service_entry_t *entries,
                                size_t cap,
                                size_t *out_len);
