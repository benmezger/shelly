#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#include "shell.h"
#include "builtins.h"
#include "getopt.h"

int shell_launch(struct command_opt *cmdinfo){
    pid_t pid, wpid;
    int status;

    pid = fork(); // now we have two processes running concurrently
    if (pid == 0){
        // child process..
        if (execvp(cmdinfo->name, cmdinfo->argv) == -1){ // program name  + string of arguments
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0){
        // error forking
        perror("shell");
    }
    else {
        // fork() executed successfully, parent process will land here.
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status)); // we use macros provided by waitpid() to wait untill the process was
        // exited or killed.
    }
    return 1;
}

int shell_execute(struct command_opt *cmdinfo){
    // int i;

    if (cmdinfo->name == NULL){
        return 1; // empty command
    }
    int i;
    for (i=0; i < shell_num_builtins(); i++){
        if (strcmp(cmdinfo->name, builtin_str[i]) == 0){
            return (*builtin_func[i])(cmdinfo->argv);
        }
    }

    // didn't match any builtin, lunch process.
    return shell_launch(cmdinfo);
}

ssize_t shell_read_line(char **line){
    size_t bufsize = 0;

    ssize_t linelen = getline(line, &bufsize, stdin);
    return linelen;
}

char *build_lprompt(void){
    char *curdir = NULL;
    curdir = getcwd(curdir, 0);
    if (curdir){
        curdir = realloc(curdir, 2 * sizeof(char *));
        if (!curdir){
            fprintf(stdout, "shell: reallocation error (%d: %s).\n", errno, strerror(errno));
        }
        return curdir;
    }
    return "> ";
}

void shell_loop(void){
    char *line;
    int status;

    ssize_t linelen;
    struct command_opt *cmdinfo;

    do {
        printf("%s $ ", build_lprompt());
        linelen = shell_read_line(&line);
        if (!*line){ /* EOF */
            fprintf(stdout, "Bye.\n");
            exit(EXIT_SUCCESS);
        }
        /* check if line is empty */
        if ((line != NULL) && (line[0] != '\0') && linelen > 1){
            cmdinfo = shell_getopts(line);
            status = shell_execute(cmdinfo);

            free(cmdinfo);
        }
        else {
            status = 1;
        }
    } while (status);
    free(line);
}

