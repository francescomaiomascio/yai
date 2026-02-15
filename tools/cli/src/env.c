// tools/cli/src/env.c

#include "../include/yai_env.h"
#include <stdlib.h>

/* ------------------------------------------------------------
   Generic env getter
------------------------------------------------------------ */

const char *yai_env_get(const char *key, const char *fallback)
{
    if (!key || key[0] == '\0')
        return fallback;

    const char *v = getenv(key);

    if (v && v[0] != '\0')
        return v;

    return fallback;
}

/* ------------------------------------------------------------
   Home resolution (authoritative order)
   1) YAI_HOME        → explicit override
   2) HOME            → standard Unix
   3) USERPROFILE     → Windows-like fallback
------------------------------------------------------------ */

const char *yai_env_home(void)
{
    const char *h;

    /* Sovereign override */
    h = getenv("YAI_HOME");
    if (h && h[0] != '\0')
        return h;

    /* POSIX */
    h = getenv("HOME");
    if (h && h[0] != '\0')
        return h;

    /* Windows fallback */
    h = getenv("USERPROFILE");
    if (h && h[0] != '\0')
        return h;

    return NULL;
}
