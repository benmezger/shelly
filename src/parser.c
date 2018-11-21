#include <stdlib.h>
#include <stdio.h>
#include <yaml.h>

#include "array.h"
#include "env.h"

struct node_list *parse_yaml(char *filename){
    yaml_parser_t parser;
    FILE *file;

    file = fopen(filename, "rb");
    if (!file){
        fprintf(stderr, "Error opening config file (%s)\n", filename);
        return NULL;
    }

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, file);

    struct node_list *env_vars = new_list(1, 1);

    /*
     * state = 0: expect key
     * state = 1: expect value
     */
    int state = 0;
    char **datap;
    unsigned char *tk;
    yaml_token_t token;

    struct node_list *env_list = new_list(1, 1);

    do {
        yaml_parser_scan(&parser, &token);
        struct vars *var = malloc(sizeof(struct vars *));

        switch (token.type){
            case YAML_KEY_TOKEN:
                state = 0;
                break;
            case YAML_VALUE_TOKEN:
                state = 1;
                break;
            case YAML_SCALAR_TOKEN:
                tk = token.data.scalar.value;
                /* key */
                if (state == 0){
                    var->key = malloc(strlen((char *) tk) + 1);
                    strcpy(var->key, (char *) tk);
                }
                else {
                    var->value = malloc(strlen((char *) tk) + 1);
                    strcpy(var->value, (char *) tk);
                    append(env_list, var);
                    free(var);
                    var = NULL;
                }
            default:
                break;
        }

        if (token.type != YAML_STREAM_END_TOKEN)
            yaml_token_delete(&token);

    } while (token.type != YAML_STREAM_END_TOKEN);

    yaml_token_delete(&token);
    yaml_parser_delete(&parser);
    fclose(file);

    return env_list;
}

int main(void){
    parse_yaml("foo.yml");
}
