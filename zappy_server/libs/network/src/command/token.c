/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-anthony.faure
** File description:
** token
*/

#include "command.h"

void free_token(node_t *node)
{
    MY_FREE(node->data);
    MY_FREE(node);
}

node_t *create_token(char *token)
{
    node_t *new = malloc(sizeof(*new));

    if (!new)
        PERROR("Failed to create new token.", NULL);
    new->data = token;
    return new;
}

char *extract_token(char **reader)
{
    char *token = NULL;
    size_t len = 0;

    if ((*reader)[0] == '\"') {
        len = strcspn(&(*reader)[1], QUOTE);
        if (!strchr(&(*reader)[1], '\"'))
            ERROR("Closing quote not found.", NULL);
        if (!(token = calloc(sizeof(*token), len + 3)))
            ERROR("Token allocation failed.", NULL);
        memmove(token, (*reader), len + 2);
        (*reader) += len + 2;
        return token;
    }
    len = strcspn((*reader), DELIM);
    if (!(token = calloc(sizeof(*token), len + 1)))
        ERROR("Token allocation failed.", NULL);
    memmove(token, (*reader), len);
    (*reader) += len;
    return token;
}
