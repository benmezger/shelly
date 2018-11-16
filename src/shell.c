#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#include <readline/readline.h>

#include "shell.h"
#include "builtins.h"
#include "getopt.h"
#include "input.h"

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

void shell_loop(void){
    char *line;
    int status;

    ssize_t linelen;
    struct command_opt *cmdinfo;
    rl_attempted_completion_function = path_file_completion;
    do {
        /* is EOF? */
        linelen = shell_read_line(&line) < 0 ? 0 : 1;

        if (linelen){
            cmdinfo = shell_getopts(line);
            status = shell_execute(cmdinfo);

            free(cmdinfo);
            free(line);
        }
        else {
            status = 0;
            fprintf(stdout, "\nBye.\n");
        }
    } while (status);
    free(line);
}

