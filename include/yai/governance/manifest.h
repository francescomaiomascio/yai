#pragma once

#include <stddef.h>

#define YAI_GOVERNANCE_PATH_MAX 512
#define YAI_GOVERNANCE_ID_MAX 96
#define YAI_GOVERNANCE_NOTE_MAX 160

typedef struct yai_law_manifest {
  char law_version[32];
  char domain_index_ref[YAI_GOVERNANCE_PATH_MAX];
  char compliance_index_ref[YAI_GOVERNANCE_PATH_MAX];
  char resolution_entrypoints_ref[YAI_GOVERNANCE_PATH_MAX];
} yai_law_manifest_t;

typedef struct yai_law_runtime_entrypoint {
  char entrypoint_id[YAI_GOVERNANCE_ID_MAX];
  char law_manifest_ref[YAI_GOVERNANCE_PATH_MAX];
  char domains_ref[YAI_GOVERNANCE_PATH_MAX];
  char compliance_ref[YAI_GOVERNANCE_PATH_MAX];
  char resolution_order_ref[YAI_GOVERNANCE_PATH_MAX];
  char compatibility_ref[YAI_GOVERNANCE_PATH_MAX];
} yai_law_runtime_entrypoint_t;

typedef struct yai_law_compatibility {
  char profile[64];
  char law_version[32];
  char runtime_target[64];
} yai_law_compatibility_t;

typedef struct yai_law_runtime_view {
  char domain_resolution_ref[YAI_GOVERNANCE_PATH_MAX];
  char compliance_resolution_ref[YAI_GOVERNANCE_PATH_MAX];
} yai_law_runtime_view_t;
