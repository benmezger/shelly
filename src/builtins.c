#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "builtins.h"

// array of function pointers (that takes and array of strings and returns and int)
int (*builtin_func[]) (char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit
};

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int shell_num_builtins(){
    return sizeof(builtin_str) / sizeof(char *);
}

int shell_cd(char **args){
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;

    if (args[1] == NULL){
        const char *homedir = NULL;
        homedir = pw->pw_dir;

        if (chdir(homedir) != 0)
            fprintf(stderr, "Error: Shell error (%d: %s)\n", errno, strerror(errno));
    }
    else {
        if (chdir(args[1]) != 0){
            fprintf(stderr, "Error: Shell error (%d: %s)\n", errno, strerror(errno));
        }
    }
    return 1;
}

int shell_help(char **args){
    int i;
    printf("Ben Mezger's shell\n");
    printf("Type program name and arguments, and hit enter.\n");
    printf("the following are builtins:\n");

    for (i=0; i < shell_num_builtins(); i++){
        printf(" %s\n", builtin_str[i]);
    }

    printf("Use man command for information about other programs.\n");
    return 1;
}


int shell_exit(char **args){
    return 0;
}

