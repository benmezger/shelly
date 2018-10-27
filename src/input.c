#include <stdio.h>
#include <string.h>
#include <readline/readline.h>

#include "input.h"
#include "prompt.h"

ssize_t shell_read_line(char **line){
   *line = readline(build_lprompt());
   if (line && *line)
       add_history(*line);
    return *line == NULL ? CTRL_D : strlen(*line);
}
