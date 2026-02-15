#ifndef YAI_CMD_H
#define YAI_CMD_H

#include "yai_cli.h"

/* Top-level dispatcher */
int yai_cmd_dispatch(
    const char *binary,
    int argc,
    char **argv,
    const yai_cli_opts_t *opt);

/* Machine Plane */
int yai_cmd_root(
    int argc,
    char **argv,
    const yai_cli_opts_t *opt);

/* L1: Kernel */
int yai_cmd_kernel(
    int argc,
    char **argv,
    const yai_cli_opts_t *opt);

/* L1: Workspace registry */
int yai_cmd_ws(
    int argc,
    char **argv,
    const yai_cli_opts_t *opt);

/* L2: Engine */
int yai_cmd_engine(
    int argc,
    char **argv,
    const yai_cli_opts_t *opt);

/* L3: Mind */
int yai_cmd_mind(
    int argc,
    char **argv,
    const yai_cli_opts_t *opt);

/* LAW */
int yai_cmd_law(
    int argc,
    char **argv,
    const yai_cli_opts_t *opt);

/* Orchestrator */
int yai_cmd_up(
    int argc,
    char **argv,
    const yai_cli_opts_t *opt);

#endif
