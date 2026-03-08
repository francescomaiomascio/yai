#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#include <yai/api/runtime.h>
#include <yai/api/version.h>
#include <yai/brain/brain.h>
#include <yai/brain/cognition.h>
#include <yai/core/dispatch.h>
#include <yai/core/lifecycle.h>
#include <yai/exec/transport_client.h>
#include <yai/exec/runtime.h>

typedef enum yai_cli_mode
{
  YAI_CLI_MODE_INVALID = -1,
  YAI_CLI_MODE_HELP = 0,
  YAI_CLI_MODE_RUN,
  YAI_CLI_MODE_STATUS,
  YAI_CLI_MODE_BRAIN_CHECK,
  YAI_CLI_MODE_PREFLIGHT,
  YAI_CLI_MODE_EXEC_PROBE
} yai_cli_mode_t;

static volatile sig_atomic_t g_runtime_stop = 0;

static void yai_on_signal(int sig)
{
  (void)sig;
  g_runtime_stop = 1;
}

static int yai_runtime_path_from_rel(const char *rel, char *out, size_t out_cap)
{
  const char *home = getenv("HOME");
  if (!rel || !rel[0] || !out || out_cap == 0 || !home || !home[0])
  {
    return -1;
  }
  if (snprintf(out, out_cap, "%s/%s", home, rel) >= (int)out_cap)
  {
    return -1;
  }
  return 0;
}

static int yai_runtime_socket_path(char *out, size_t out_cap)
{
  return yai_runtime_path_from_rel(YAI_RUNTIME_INGRESS_SOCKET_REL, out, out_cap);
}

static int yai_runtime_pidfile_path(char *out, size_t out_cap)
{
  return yai_runtime_path_from_rel(YAI_RUNTIME_PIDFILE_REL, out, out_cap);
}

static int yai_runtime_socket_exists(const char *socket_path)
{
  struct stat st;
  if (!socket_path || !socket_path[0])
  {
    return 0;
  }
  if (stat(socket_path, &st) != 0)
  {
    return 0;
  }
  return S_ISSOCK(st.st_mode) ? 1 : 0;
}

static int yai_runtime_is_reachable(void)
{
  yai_rpc_client_t client = {0};
  int rc = yai_rpc_connect(&client, "system");
  if (rc != 0)
  {
    return 0;
  }
  rc = yai_rpc_handshake(&client, 0);
  yai_rpc_close(&client);
  return rc == 0 ? 1 : 0;
}

static int yai_runtime_pid_is_alive(pid_t pid)
{
  if (pid <= 0)
  {
    return 0;
  }
  return kill(pid, 0) == 0 ? 1 : 0;
}

static int yai_runtime_read_pidfile(const char *pidfile_path, pid_t *pid_out)
{
  FILE *f = NULL;
  long pid_raw = 0;

  if (!pidfile_path || !pidfile_path[0] || !pid_out)
  {
    return -1;
  }

  f = fopen(pidfile_path, "r");
  if (!f)
  {
    return -1;
  }

  if (fscanf(f, "%ld", &pid_raw) != 1)
  {
    fclose(f);
    return -1;
  }
  fclose(f);

  if (pid_raw <= 0)
  {
    return -1;
  }

  *pid_out = (pid_t)pid_raw;
  return 0;
}

static int yai_runtime_write_pidfile(const char *pidfile_path)
{
  FILE *f = NULL;

  if (!pidfile_path || !pidfile_path[0])
  {
    return -1;
  }

  f = fopen(pidfile_path, "w");
  if (!f)
  {
    return -1;
  }

  fprintf(f, "%ld\n", (long)getpid());
  fclose(f);
  return 0;
}

static void yai_runtime_remove_pidfile(const char *pidfile_path)
{
  if (pidfile_path && pidfile_path[0])
  {
    (void)unlink(pidfile_path);
  }
}

static int yai_install_signal_handlers(void)
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = yai_on_signal;
  sigemptyset(&sa.sa_mask);

  if (sigaction(SIGINT, &sa, NULL) != 0)
  {
    return -1;
  }
  if (sigaction(SIGTERM, &sa, NULL) != 0)
  {
    return -1;
  }
  return 0;
}

static int yai_runtime_serve_loop(const char *socket_path)
{
  int listener_fd = yai_control_listen_at(socket_path);
  if (listener_fd < 0)
  {
    fprintf(stderr, "yai: failed to open ingress socket (%s)\n", socket_path);
    return 1;
  }

  printf("yai: runtime ingress listening on %s\n", socket_path);

  while (!g_runtime_stop)
  {
    int client_fd = accept(listener_fd, NULL, NULL);
    if (client_fd < 0)
    {
      if (errno == EINTR)
      {
        continue;
      }
      perror("yai: accept failed");
      close(listener_fd);
      unlink(socket_path);
      return 1;
    }

    {
      int handshake_done = 0;
      while (!g_runtime_stop)
      {
        yai_rpc_envelope_t env;
        char payload[YAI_MAX_PAYLOAD];
        ssize_t payload_len = yai_control_read_frame(client_fd, &env, payload, sizeof(payload));
        if (payload_len < 0)
        {
          break;
        }
        if (yai_dispatch_frame(client_fd, &env, payload, payload_len, &handshake_done) != 0)
        {
          break;
        }
      }
    }

    close(client_fd);
  }

  close(listener_fd);
  unlink(socket_path);
  puts("yai: runtime stopped");
  return 0;
}

static void yai_print_help(void)
{
  puts("yai - runtime entrypoint");
  printf("version: %s\n", YAI_VERSION_STRING);
  puts("");
  puts("usage:");
  puts("  yai up                start persistent runtime ingress (foreground)");
  puts("  yai status            runtime diagnostics and ingress reachability");
  puts("  yai brain-check       cognition/runtime smoke");
  puts("  yai preflight         core preflight checks");
  puts("  yai exec-probe        execution plane probe");
  puts("  yai help              show this help");
  puts("  yai --help            show this help");
  puts("");
  puts("notes:");
  puts("  - yai is the canonical runtime binary");
  puts("  - canonical ingress: $HOME/.yai/run/control.sock");
  puts("  - core, exec and brain are internal runtime modules");
}

static yai_cli_mode_t yai_parse_mode(int argc, char **argv)
{
  if (argc <= 1)
  {
    return YAI_CLI_MODE_HELP;
  }

  if (strcmp(argv[1], "--help") == 0 ||
      strcmp(argv[1], "-h") == 0 ||
      strcmp(argv[1], "help") == 0)
  {
    return YAI_CLI_MODE_HELP;
  }

  if (strcmp(argv[1], "up") == 0)
  {
    return YAI_CLI_MODE_RUN;
  }

  if (strcmp(argv[1], "status") == 0)
  {
    return YAI_CLI_MODE_STATUS;
  }

  if (strcmp(argv[1], "brain-check") == 0)
  {
    return YAI_CLI_MODE_BRAIN_CHECK;
  }

  if (strcmp(argv[1], "preflight") == 0)
  {
    return YAI_CLI_MODE_PREFLIGHT;
  }

  if (strcmp(argv[1], "exec-probe") == 0)
  {
    return YAI_CLI_MODE_EXEC_PROBE;
  }

  return YAI_CLI_MODE_INVALID;
}

static int yai_run_preflight(void)
{
  int rc = yai_run_preboot_checks();
  if (rc != 0)
  {
    fprintf(stderr, "yai: preboot checks failed (rc=%d)\n", rc);
    return 1;
  }

  rc = yai_ensure_runtime_layout(NULL);
  if (rc != 0)
  {
    fprintf(stderr, "yai: runtime layout failed (rc=%d)\n", rc);
    return 1;
  }

  puts("yai: preflight OK");
  return 0;
}

static int yai_run_exec_probe(void)
{
  int state = yai_exec_runtime_probe();

  printf("yai: exec runtime state=%s (%d)\n",
         yai_exec_runtime_state_name((yai_exec_runtime_state_t)state),
         state);

  return (state >= 0) ? 0 : 1;
}

static int yai_run_brain_check(void)
{
  yai_mind_config_t cfg = {
      .runtime_name = "yai",
      .enable_mock_provider = 1};
  yai_mind_cognition_response_t out = {0};
  int rc = 0;

  rc = yai_mind_init(&cfg);
  if (rc != YAI_MIND_OK)
  {
    fprintf(stderr, "yai: brain init failed (%d)\n", rc);
    return 1;
  }

  rc = yai_mind_cognition_execute_text("brain check",
                                       "yai-check",
                                       "mock",
                                       &out);
  if (rc != YAI_MIND_OK)
  {
    fprintf(stderr, "yai: brain cognition probe failed (%d)\n", rc);
    (void)yai_mind_shutdown();
    return 1;
  }

  printf("yai: brain check OK role=%s score=%.2f\n",
         yai_mind_agent_role_name(out.selected_role),
         out.score);

  return (yai_mind_shutdown() == YAI_MIND_OK) ? 0 : 1;
}

static int yai_run_status(void)
{
  char socket_path[256] = {0};
  char pidfile_path[256] = {0};
  pid_t pid = 0;
  int preboot = yai_run_preboot_checks();
  int layout = yai_ensure_runtime_layout(NULL);
  int exec_state = yai_exec_runtime_probe();
  int socket_ok = yai_runtime_socket_path(socket_path, sizeof(socket_path)) == 0;
  int pidfile_ok = yai_runtime_pidfile_path(pidfile_path, sizeof(pidfile_path)) == 0;
  int socket_exists = socket_ok ? yai_runtime_socket_exists(socket_path) : 0;
  int pidfile_exists = pidfile_ok && access(pidfile_path, F_OK) == 0;
  int pid_alive = (pidfile_exists && yai_runtime_read_pidfile(pidfile_path, &pid) == 0)
                      ? yai_runtime_pid_is_alive(pid)
                      : 0;
  int reachable = socket_ok ? yai_runtime_is_reachable() : 0;

  printf("yai: status core.preboot=%d core.layout=%d exec.state=%s(%d) ingress.socket=%s ingress.socket_exists=%d ingress.reachable=%d runtime.pidfile=%s runtime.pid_alive=%d\n",
         preboot,
         layout,
         yai_exec_runtime_state_name((yai_exec_runtime_state_t)exec_state),
         exec_state,
         socket_ok ? socket_path : "<unresolved>",
         socket_exists,
         reachable,
         pidfile_ok ? pidfile_path : "<unresolved>",
         pid_alive);

  return (preboot == 0 && layout == 0 && exec_state >= 0 && reachable == 1) ? 0 : 1;
}

static int yai_run_runtime(void)
{
  char socket_path[256] = {0};
  char pidfile_path[256] = {0};
  int pidfile_written = 0;
  yai_mind_config_t cfg = {
      .runtime_name = "yai-runtime",
      .enable_mock_provider = 1};
  int rc = 0;

  puts("yai: preparing runtime...");
  rc = yai_run_preflight();
  if (rc != 0)
  {
    return rc;
  }

  puts("yai: probing exec plane...");
  rc = yai_run_exec_probe();
  if (rc != 0)
  {
    return rc;
  }

  if (yai_runtime_socket_path(socket_path, sizeof(socket_path)) != 0 ||
      yai_runtime_pidfile_path(pidfile_path, sizeof(pidfile_path)) != 0)
  {
    fprintf(stderr, "yai: failed to resolve runtime paths\n");
    return 1;
  }

  if (yai_runtime_is_reachable())
  {
    fprintf(stderr, "yai: runtime already active on %s\n", socket_path);
    return 1;
  }

  if (yai_install_signal_handlers() != 0)
  {
    fprintf(stderr, "yai: failed to install signal handlers\n");
    return 1;
  }

  puts("yai: initializing brain module...");
  rc = yai_mind_init(&cfg);
  if (rc != YAI_MIND_OK)
  {
    fprintf(stderr, "yai: brain init failed (%d)\n", rc);
    return 1;
  }

  if (yai_runtime_write_pidfile(pidfile_path) != 0)
  {
    fprintf(stderr, "yai: warning: failed to write runtime pidfile (%s)\n", pidfile_path);
  }
  else
  {
    pidfile_written = 1;
  }

  puts("yai: runtime is live; press Ctrl+C to stop");
  rc = yai_runtime_serve_loop(socket_path);

  if (pidfile_written)
  {
    yai_runtime_remove_pidfile(pidfile_path);
  }

  if (yai_mind_shutdown() != YAI_MIND_OK)
  {
    fprintf(stderr, "yai: brain shutdown failed\n");
    return 1;
  }

  return rc;
}

int main(int argc, char **argv)
{
  yai_cli_mode_t mode = yai_parse_mode(argc, argv);

  switch (mode)
  {
  case YAI_CLI_MODE_HELP:
    yai_print_help();
    return 0;

  case YAI_CLI_MODE_RUN:
    return yai_run_runtime();

  case YAI_CLI_MODE_STATUS:
    return yai_run_status();

  case YAI_CLI_MODE_BRAIN_CHECK:
    return yai_run_brain_check();

  case YAI_CLI_MODE_PREFLIGHT:
    return yai_run_preflight();

  case YAI_CLI_MODE_EXEC_PROBE:
    return yai_run_exec_probe();

  case YAI_CLI_MODE_INVALID:
  default:
    fprintf(stderr, "yai: unknown command '%s'\n",
            (argc > 1 && argv[1]) ? argv[1] : "<null>");
    yai_print_help();
    return 2;
  }
}
