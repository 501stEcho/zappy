/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** look_parse
*/

#include "stdlib.h"
#include "string.h"

char *parse_response(char *str)
{
    int length = strlen(str);
    char *res = calloc((2 * length + 3), sizeof(char));
    int j = 0;

    for (unsigned int i = 0; str[i]; i++) {
        if (j && res[j - 1] && res[j - 1] == '[')
            res[j++] = ' ';
        if (str[i] == ']' && res[j - 1] != ' ')
            res[j++] = ' ';
        res[j] = str[i];
        if (str[i] == ',' && str[i + 1] && str[i + 1] != ',')
            res[++j] = ' ';
        if (res[j] == '|')
            res[j] = ' ';
        j++;
    }
    free(str);
    return res;
}
