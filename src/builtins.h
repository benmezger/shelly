#ifndef BULTINS_H
#define BULTINS_H

int shell_cd(char **);

int shell_help(void);

int shell_exit(char **);

char *builtin_str[3];

// array of function pointers (that takes and array of strings and returns and int)
int (*builtin_func[3]) (char **);

int shell_num_builtins(void);

#endif
