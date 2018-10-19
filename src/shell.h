#ifndef SHELL_H
#define SHELL_H

#define SHELL_RL_BUFSIZE 1024
#define SHELL_TOK_BUFSIZE 64
#define SHELL_TOK_DELIM " \t\r\n\a"

char **shell_split_line(char *);

int shell_launch(char **);

int shell_execute(char **);

char *shell_read_line(void);

void shell_loop(void);

#endif
