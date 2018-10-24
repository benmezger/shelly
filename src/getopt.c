#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "shell.h"
#include "getopt.h"

struct command_opt *parse_opts(int bufsize, int argc, char **argv){
    struct command_opt *cmdopt = malloc(sizeof(struct command_opt));
    cmdopt->argc = argc;
    cmdopt->name = argv[0]; /* program name */
    /* TODO: Using more memory than needed. */
    cmdopt->argv = malloc((bufsize - sizeof(cmdopt->name)) * sizeof(char *));

    int cur = 0; /* start by one skipping program name */
    while (cur < argc){
        cmdopt->argv[cur] = argv[cur];
        cur++;
    }
    return cmdopt;
}

/*
int is_empty(const char *line){
    while (*line != '\0'){
        if (!isspace((unsigned char *) *line))
            return 0;
        line++;
    }
    return 1;
}
*/

char *clean_str(char *str){
    char *end;

    while (isspace((unsigned char) *str))
        str++;
    if (*str == 0) /* all spaces? */
        return str;

    /* trim trailing spaces */
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end))
        end--;

    end[1] = '\0';
    return str;
}


struct command_opt *shell_getopts(char *line){
    int bufsize = SHELL_TOK_BUFSIZE;
    char **argv = malloc(bufsize * sizeof(char *));

    if (!argv){
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    int pos = 0;
    char *token = strtok(line, ARG_DELIMITER);

    while (token != NULL){
        token = clean_str(token);
        argv[pos] = token;
        pos++;

        if (pos >= bufsize){
            bufsize += SHELL_TOK_BUFSIZE;
            argv = realloc(argv, bufsize * sizeof(char *));
            if (!argv){
                fprintf(stdout, "shell: reallocation error (%d: %s).\n", errno, strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, ARG_DELIMITER);
    }
    argv[pos] = NULL;
    struct command_opt *args = parse_opts(bufsize, pos, argv);
    return args;
}

// int main(){
//     char *line = malloc(SHELL_TOK_BUFSIZE * 64);
//     strcpy(line, "foo -a -b -l --less --random=12");
//     shell_getopts(line);
// }
