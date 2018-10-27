#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

#define CTRL_D -1 /* EOF */

ssize_t shell_read_line(char **);

#endif
