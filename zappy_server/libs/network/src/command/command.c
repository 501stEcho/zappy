/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** command
*/

#include "command.h"

void free_command(command_t *command)
{
    for (uint16_t i = 0; command->segments[i]; ++i)
        MY_FREE(command->segments[i]);
    MY_FREE(command->segments);
    MY_FREE(command);
}

command_t *create_command(head_t *tokens, uint16_t nb_segments)
{
    command_t *command = NULL;
    node_t *entry = NULL;
    uint16_t index = nb_segments - 1;

    if (!(command = malloc(sizeof(*command))) ||
        !(command->segments = calloc(nb_segments + 1,
        sizeof(*command->segments)))) {
        MY_FREE(command);
        free_list(tokens, &free_token);
        PERROR("Command segements allocation failed.", NULL);
    }
    while (!LIST_EMPTY(tokens)) {
        entry = LIST_FIRST(tokens);
        LIST_REMOVE(entry, entries);
        command->segments[index--] = entry->data;
        MY_FREE(entry);
    }
    command->nb_segments = nb_segments;
    return command;
}

command_t *get_command(char *buffer)
{
    char *token = NULL;
    node_t *elm = NULL;
    uint16_t nb_segments = 0;
    head_t tokens;
    ssize_t start = 0;
    LIST_INIT(&tokens);

    while (buffer[0]) {
        start = strspn(buffer, WHITE_SPACES);
        if (!buffer[start])
            break;
        buffer += start;
        if (!(token = extract_token(&buffer)) || !(elm = create_token(token))) {
            free_list(&tokens, &free_token);
            ERROR("Token creation failed", NULL);
        }
        ++nb_segments;
        LIST_INSERT_HEAD(&tokens, elm, entries);
    }
    return create_command(&tokens, nb_segments);
}
