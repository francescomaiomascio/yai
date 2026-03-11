#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <yai/daemon/runtime.h>
#include <yai/platform/os.h>
#include <yai/exec/source_plane.h>

#include "internal.h"

void yai_daemon_log(const yai_daemon_runtime_t *rt, const char *level, const char *message)
{
  yai_daemon_logf(rt, level, "%s", message ? message : "");
}

void yai_daemon_logf(const yai_daemon_runtime_t *rt, const char *level, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  yai_daemon_vlog(rt ? rt->instance_id : NULL, level, fmt, ap);
  va_end(ap);
}

static int write_identity(const yai_daemon_runtime_t *rt)
{
  char payload[1024];
  if (!rt)
  {
    return -1;
  }
  if (snprintf(payload,
               sizeof(payload),
               "{\n"
               "  \"type\": \"yai.daemon.identity.v1\",\n"
               "  \"instance_id\": \"%s\",\n"
               "  \"source_label\": \"%s\",\n"
               "  \"owner_ref\": \"%s\",\n"
               "  \"topology\": \"%s\"\n"
               "}\n",
               rt->instance_id,
               rt->config.source_label,
               rt->config.owner_ref,
               YAI_SOURCE_PLANE_TOPOLOGY) >= (int)sizeof(payload))
  {
    return -1;
  }
  return yai_daemon_write_file(rt->paths.instance_file, payload);
}

static int write_pid(const yai_daemon_runtime_t *rt)
{
  char payload[64];
  if (!rt)
  {
    return -1;
  }
  if (snprintf(payload, sizeof(payload), "%ld\n", (long)yai_os_getpid()) >= (int)sizeof(payload))
  {
    return -1;
  }
  return yai_daemon_write_file(rt->paths.pid_file, payload);
}

int yai_daemon_runtime_init(yai_daemon_runtime_t *rt, const yai_daemon_config_t *cfg)
{
  time_t now = 0;
  if (!rt || !cfg)
  {
    return -1;
  }
  memset(rt, 0, sizeof(*rt));
  rt->config = *cfg;

  if (yai_daemon_paths_build(&rt->config, &rt->paths) != 0)
  {
    return -2;
  }
  if (yai_daemon_paths_ensure(&rt->paths) != 0)
  {
    return -3;
  }

  now = time(NULL);
  if (snprintf(rt->instance_id,
               sizeof(rt->instance_id),
               "yd-%ld-%ld",
               (long)yai_os_getpid(),
               (long)now) >= (int)sizeof(rt->instance_id))
  {
    return -4;
  }

  if (write_identity(rt) != 0)
  {
    return -5;
  }
  rt->local = (yai_daemon_local_runtime_t *)calloc(1, sizeof(*rt->local));
  if (!rt->local)
  {
    return -6;
  }
  if (yai_daemon_local_runtime_init(rt->local,
                                    &rt->config,
                                    &rt->paths,
                                    rt->instance_id,
                                    rt->config.source_label) != 0)
  {
    free(rt->local);
    rt->local = NULL;
    return -7;
  }

  yai_daemon_logf(rt,
                  "info",
                  "bootstrap complete home=%s source=%s owner=%s",
                  rt->paths.home,
                  rt->config.source_label,
                  rt->config.owner_ref[0] ? rt->config.owner_ref : "unset");
  return 0;
}

int yai_daemon_runtime_start(yai_daemon_runtime_t *rt)
{
  if (!rt)
  {
    return -1;
  }

  /* Guardrail: daemon is edge acquisition only and cannot become owner truth. */
  yai_daemon_logf(rt,
                  "info",
                  "starting instance=%s topology=%s mode=%s tick_ms=%u max_ticks=%d",
                  rt->instance_id,
                  YAI_SOURCE_PLANE_TOPOLOGY,
                  rt->config.mode,
                  rt->config.tick_ms,
                  rt->config.max_ticks);

  if (write_pid(rt) != 0)
  {
    return -2;
  }
  if (!rt->local || yai_daemon_local_runtime_start(rt->local) != 0)
  {
    return -3;
  }

  rt->running = 1;
  return 0;
}

int yai_daemon_runtime_tick(yai_daemon_runtime_t *rt)
{
  if (!rt || !rt->running)
  {
    return -1;
  }

  rt->tick_count += 1;
  if (!rt->local || yai_daemon_local_runtime_tick(rt->local, rt->tick_count) != 0)
  {
    return -2;
  }
  if ((rt->tick_count % 5U) == 0U)
  {
    yai_daemon_logf(rt, "debug", "heartbeat tick=%u", rt->tick_count);
  }
  return 0;
}

int yai_daemon_runtime_shutdown(yai_daemon_runtime_t *rt)
{
  if (!rt)
  {
    return -1;
  }
  if (rt->local)
  {
    (void)yai_daemon_local_runtime_stop(rt->local);
    free(rt->local);
    rt->local = NULL;
  }
  rt->running = 0;
  yai_daemon_logf(rt, "info", "shutdown complete ticks=%u", rt->tick_count);
  return 0;
}
