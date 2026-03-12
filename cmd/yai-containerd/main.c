#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <yai/api/version.h>
#include <yai/container/container.h>

static void print_help(void) {
  puts("yai-containerd - canonical container manager service surface");
  printf("version: %s\n", YAI_VERSION_STRING);
  puts("");
  puts("usage:");
  puts("  yai-containerd create <container-id> [interactive|managed|service|system|recovery]");
  puts("  yai-containerd initialize <container-id>");
  puts("  yai-containerd open <container-id>");
  puts("  yai-containerd attach <container-id> <session-id>");
  puts("  yai-containerd recover <container-id>");
  puts("  yai-containerd seal <container-id>");
  puts("  yai-containerd destroy <container-id>");
  puts("  yai-containerd show <container-id>");
}

static yai_container_class_t parse_class(const char *value) {
  if (!value || !value[0] || strcmp(value, "interactive") == 0) {
    return YAI_CONTAINER_CLASS_INTERACTIVE;
  }
  if (strcmp(value, "managed") == 0) {
    return YAI_CONTAINER_CLASS_MANAGED;
  }
  if (strcmp(value, "service") == 0) {
    return YAI_CONTAINER_CLASS_SERVICE;
  }
  if (strcmp(value, "system") == 0) {
    return YAI_CONTAINER_CLASS_SYSTEM;
  }
  if (strcmp(value, "recovery") == 0) {
    return YAI_CONTAINER_CLASS_RECOVERY;
  }
  return YAI_CONTAINER_CLASS_INTERACTIVE;
}

static int cmd_create(const char *container_id, const char *class_name) {
  yai_container_record_t record;
  time_t now = time(NULL);

  if (!container_id || !container_id[0]) {
    return 1;
  }

  memset(&record, 0, sizeof(record));
  strncpy(record.identity.container_id, container_id, YAI_CONTAINER_ID_MAX);
  record.identity.container_id[YAI_CONTAINER_ID_MAX] = '\0';
  record.identity.container_class = parse_class(class_name);
  strncpy(record.identity.container_profile, yai_container_class_name(record.identity.container_class), YAI_CONTAINER_PROFILE_MAX);
  record.identity.container_profile[YAI_CONTAINER_PROFILE_MAX] = '\0';
  strncpy(record.identity.creation_source, "yai-containerd", YAI_CONTAINER_SOURCE_MAX);
  record.identity.creation_source[YAI_CONTAINER_SOURCE_MAX] = '\0';
  record.identity.owner_handle = 1;
  record.identity.state_handle = (uint64_t)now;

  yai_container_config_defaults(&record.config);
  record.lifecycle.current = YAI_CONTAINER_LIFECYCLE_CREATED;
  record.lifecycle.previous = YAI_CONTAINER_LIFECYCLE_CREATED;
  record.lifecycle.created_at = (int64_t)now;
  record.lifecycle.updated_at = (int64_t)now;

  snprintf(record.root.root_path, sizeof(record.root.root_path), "/container/%s", record.identity.container_id);
  record.root.container_root_handle = record.identity.state_handle;

  record.session_domain.container_session_scope = record.identity.state_handle;

  yai_container_state_defaults(&record.state);

  if (yai_container_create(&record) != 0) {
    fprintf(stderr, "create failed for container '%s'\n", container_id);
    return 1;
  }

  printf("created container %s class=%s\n", record.identity.container_id,
         yai_container_class_name(record.identity.container_class));
  return 0;
}

static int cmd_show(const char *container_id) {
  yai_container_identity_t identity;
  yai_container_state_t state;
  yai_container_root_t root;
  yai_container_session_domain_t session;
  yai_container_policy_view_t policy;
  yai_container_grants_view_t grants;

  if (yai_container_get_identity(container_id, &identity) != 0 ||
      yai_container_get_state(container_id, &state) != 0 ||
      yai_container_get_root_view(container_id, &root) != 0 ||
      yai_container_get_session_view(container_id, &session) != 0 ||
      yai_container_get_policy_view(container_id, &policy) != 0 ||
      yai_container_get_grants_view(container_id, &grants) != 0) {
    fprintf(stderr, "show failed for container '%s'\n", container_id);
    return 1;
  }

  printf("container_id=%s\n", identity.container_id);
  printf("class=%s profile=%s source=%s\n",
         yai_container_class_name(identity.container_class),
         identity.container_profile,
         identity.creation_source);
  printf("lifecycle=%s\n", yai_container_lifecycle_name(state.lifecycle_state));
  printf("state-updated-at=%lld recovery-flags=%llu\n",
         (long long)state.updated_at,
         (unsigned long long)state.recovery_reason_flags);
  printf("root_handle=%llu projection=%s path=%s\n",
         (unsigned long long)root.container_root_handle,
         root.projection_ready ? "ready" : "not-ready",
         root.root_path);
  printf("session_bound=%u count=%llu last=%llu\n",
         (unsigned)session.bound,
         (unsigned long long)session.bound_session_count,
         (unsigned long long)session.last_bound_session_id);
  printf("policy_view=%llu grants_view=%llu\n",
         (unsigned long long)policy.policy_view_handle,
         (unsigned long long)grants.grants_view_handle);
  return 0;
}

int main(int argc, char **argv) {
  if (argc < 2 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "help") == 0) {
    print_help();
    return 0;
  }

  if (strcmp(argv[1], "create") == 0) {
    return cmd_create(argc > 2 ? argv[2] : NULL, argc > 3 ? argv[3] : NULL);
  }

  if (strcmp(argv[1], "initialize") == 0 && argc > 2) {
    return yai_container_initialize(argv[2]) == 0 ? 0 : 1;
  }

  if (strcmp(argv[1], "open") == 0 && argc > 2) {
    return yai_container_open(argv[2]) == 0 ? 0 : 1;
  }

  if (strcmp(argv[1], "attach") == 0 && argc > 3) {
    uint64_t session_id = (uint64_t)strtoull(argv[3], NULL, 10);
    return yai_container_attach(argv[2], session_id) == 0 ? 0 : 1;
  }

  if (strcmp(argv[1], "recover") == 0 && argc > 2) {
    return yai_container_recover(argv[2], 1u) == 0 ? 0 : 1;
  }

  if (strcmp(argv[1], "seal") == 0 && argc > 2) {
    return yai_container_seal_runtime(argv[2], (int64_t)time(NULL)) == 0 ? 0 : 1;
  }

  if (strcmp(argv[1], "destroy") == 0 && argc > 2) {
    return yai_container_destroy(argv[2], (int64_t)time(NULL)) == 0 ? 0 : 1;
  }

  if (strcmp(argv[1], "show") == 0 && argc > 2) {
    return cmd_show(argv[2]);
  }

  print_help();
  return 1;
}
