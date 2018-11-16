#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

#define CTRL_D -1 /* EOF */

ssize_t shell_read_line(char **);

char **path_file_completion(const char *, int, int);
char **path_file_generator(const char *, int);

#endif
