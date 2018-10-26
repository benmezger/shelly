#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "prompt.h"

char *_build_path_completion(void){}

char *build_lprompt(void){
    char *curdir = NULL;
    curdir = getcwd(curdir, 0);
    if (curdir){
        curdir = realloc(curdir, strlen(curdir) + (3 * sizeof(char *)));
        snprintf(curdir + strlen(curdir), 3 - strlen(curdir), " %s ", "$");
        if (!curdir){
            fprintf(stdout, "shell: reallocation error (%d: %s).\n", errno, strerror(errno));
        }
        return curdir;
    }
    fprintf(stdout, "shell: error getting current directory. (%d: %s).\n", errno, strerror(errno));
    return "> ";
}
