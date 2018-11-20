#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <dirent.h>
#include <sys/types.h>

#include "input.h"
#include "prompt.h"
#include "shell.h"
#include "array.h"

void get_path_files(char *path, struct node_list *exec_files){
    DIR *dp;
    struct dirent *ep;
    dp = opendir(path);

    if (dp != NULL){
        while ((ep = readdir(dp))){
            if (strlen(ep->d_name) > 0 && strcmp(ep->d_name, ".")\
                    && strcmp(ep->d_name, "..")){
                append(exec_files, (void *) ep->d_name);
            }
        }
        closedir(dp);
    }
    else {
        ;;
    }
}

struct node_list *files_in_path(void){
    char *paths = getenv("PATH");
    struct node_list *files = new_list(1, 1);
    if (!paths)
        return NULL;

    char *token = strtok(paths, ":");
    while (token != NULL){
        get_path_files(token, files);
        token = strtok(NULL, ":");
    }
    return files;
}

char **path_file_completion(const char *text, int start, int end){
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, path_file_generator);
}

char **path_file_generator(const char *text, int state){
    static int list_index;
    static int len;

    if (!state){
        list_index = 0;
        len = strlen(text);
    }

    struct node_list *it = files_in_path();
    struct node *cur = it->head->next; /* head if NULL/NULL */
    while (cur->next != NULL){
        if (strncmp((char *) cur->data, text, len) == 0){
            return (char **) strdup(cur->data);
        }
        cur = cur->next;
    }
    return NULL;
}

ssize_t shell_read_line(char **line){
   *line = readline(build_lprompt());
   if (line && *line)
       add_history(*line);
    return *line == NULL ? CTRL_D : strlen(*line);
}
