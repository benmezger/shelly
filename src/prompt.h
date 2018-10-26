#ifndef PROMPT_H
#define PROMPT_H

char *build_lprompt(void);

char **character_name_completion(const char *, int, int);

char *character_name_generator(const char *, int);


#endif
