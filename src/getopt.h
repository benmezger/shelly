#ifndef GETOPT_H
#define GETOPT_H

#define ARG_DELIMITER " "
#define DELIMITERS "\n\t\a "

struct command_opt {
    char *name; /* program name */
    int argc; /* number of arguments */
    char **argv; /* arguments */
};

struct command_opt *parse_opts(int, int, char **);

struct command_opt *shell_getopts(char *);

char *clean_str(char *);

#endif
