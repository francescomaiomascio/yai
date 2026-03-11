#include "../internal.h"

#include <stdio.h>
#include <string.h>

int yai_law_manifest_load(yai_law_runtime_t *rt, char *err, size_t err_cap) {
  char path[512];
  char json[4096];

  if (!rt) return -1;

  if (yai_law_safe_snprintf(path, sizeof(path), "%s/law.manifest.json", rt->root) != 0) return -1;
  if (yai_law_read_text_file(path, json, sizeof(json)) != 0) {
    if (err && err_cap) (void)yai_law_safe_snprintf(err, err_cap, "cannot read %s", path);
    return -1;
  }

  (void)yai_law_json_extract_string(json, "law_version", rt->manifest.law_version, sizeof(rt->manifest.law_version));
  (void)yai_law_json_extract_string(json, "domain_index_ref", rt->manifest.domain_index_ref, sizeof(rt->manifest.domain_index_ref));
  (void)yai_law_json_extract_string(json, "compliance_index_ref", rt->manifest.compliance_index_ref, sizeof(rt->manifest.compliance_index_ref));
  (void)yai_law_json_extract_string(json, "resolution_entrypoints_ref", rt->manifest.resolution_entrypoints_ref, sizeof(rt->manifest.resolution_entrypoints_ref));

  if (yai_law_safe_snprintf(path, sizeof(path), "%s/runtime.entrypoints.json", rt->root) != 0) return -1;
  if (yai_law_read_text_file(path, json, sizeof(json)) != 0) {
    if (err && err_cap) (void)yai_law_safe_snprintf(err, err_cap, "cannot read %s", path);
    return -1;
  }

  (void)yai_law_json_extract_string(json, "entrypoint_id", rt->entrypoint.entrypoint_id, sizeof(rt->entrypoint.entrypoint_id));
  (void)yai_law_json_extract_string(json, "law_manifest_ref", rt->entrypoint.law_manifest_ref, sizeof(rt->entrypoint.law_manifest_ref));
  (void)yai_law_json_extract_string(json, "domains_ref", rt->entrypoint.domains_ref, sizeof(rt->entrypoint.domains_ref));
  (void)yai_law_json_extract_string(json, "compliance_ref", rt->entrypoint.compliance_ref, sizeof(rt->entrypoint.compliance_ref));
  (void)yai_law_json_extract_string(json, "resolution_order_ref", rt->entrypoint.resolution_order_ref, sizeof(rt->entrypoint.resolution_order_ref));
  (void)yai_law_json_extract_string(json, "compatibility_ref", rt->entrypoint.compatibility_ref, sizeof(rt->entrypoint.compatibility_ref));

  if (rt->entrypoint.entrypoint_id[0] == '\0') {
    (void)yai_law_safe_snprintf(rt->entrypoint.entrypoint_id, sizeof(rt->entrypoint.entrypoint_id), "%s", "default-runtime");
  }

  if (yai_law_safe_snprintf(path, sizeof(path), "%s/manifests/domain-resolution-order.json", rt->root) == 0) {
    (void)yai_law_safe_snprintf(rt->runtime_view.domain_resolution_ref, sizeof(rt->runtime_view.domain_resolution_ref), "%s", path);
  }
  if (yai_law_safe_snprintf(path, sizeof(path), "%s/manifests/compliance-resolution-order.json", rt->root) == 0) {
    (void)yai_law_safe_snprintf(rt->runtime_view.compliance_resolution_ref, sizeof(rt->runtime_view.compliance_resolution_ref), "%s", path);
  }

  return 0;
}
