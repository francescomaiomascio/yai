#ifndef YAI_CMD_H
#define YAI_CMD_H

#include "yai_cli.h"

int yai_cmd_dispatch(const char *binary, int argc, char **argv, const yai_cli_opts_t *opt);

// Aggiungi 'const' a tutti i prototipi qui sotto
int yai_cmd_kernel(int argc, char **argv, const yai_cli_opts_t *opt);
int yai_cmd_ws(int argc, char **argv, const yai_cli_opts_t *opt);
int yai_cmd_engine(int argc, char **argv, const yai_cli_opts_t *opt);
int yai_cmd_mind(int argc, char **argv, const yai_cli_opts_t *opt);
int yai_cmd_law(int argc, char **argv, const yai_cli_opts_t *opt);

#endif