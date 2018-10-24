#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>

#include "getopt.h"

#define SHELL_RL_BUFSIZE 1024
#define SHELL_TOK_BUFSIZE 64

int shell_launch(struct command_opt *);

int shell_execute(struct command_opt *);

ssize_t shell_read_line(char **);

void shell_loop(void);

#endif
