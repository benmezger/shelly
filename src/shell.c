#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

#include "shell.h"
#include "builtins.h"

char **shell_split_line(char *line){
    int bufsize = SHELL_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens){
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SHELL_TOK_DELIM);
    while (token != NULL){
        tokens[position] = token;
        position++;

        if (position >= bufsize){
            bufsize += SHELL_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens){
                fprintf(stderr, "shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, SHELL_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int shell_launch(char **args){
    pid_t pid, wpid;
    int status;

    pid = fork(); // now we have two processes running concurrently
    if (pid == 0){
        // child process..
        if (execvp(args[0], args) == -1){ // program name  + string of arguments
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

int shell_execute(char **args){
    int i;

    if (args[0] == NULL){
        return 1; // empty command
    }

    for (i=0; i < shell_num_builtins(); i++){
        if (strcmp(args[0], builtin_str[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }

    // didn't match any builtin, lunch process.
    return shell_launch(args);
}

char *shell_read_line(void){
    char *line = NULL;
    size_t bufsize = 0;

    getline(&line, &bufsize, stdin);
    return line;
}

void shell_loop(void){
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = shell_read_line();
        if (!*line){ /* EOF */
            fprintf(stdout, "Bye.\n");
            exit(EXIT_SUCCESS);
        }

        args = shell_split_line(line);
        status = shell_execute(args);

        free(line);
        free(args);
    } while (status);
}

