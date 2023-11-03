/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** ai_command
*/

#include "zappy_server.h"
#include "protocol.h"
#include "ai.h"

const command_execution_time_t ai_command_time[] = {
    {&ai_commands[0], NULL, 7},
    {&ai_commands[1], NULL, 7},
    {&ai_commands[2], NULL, 7},
    {&ai_commands[3], NULL, 7},
    {&ai_commands[4], NULL, 1},
    {&ai_commands[5], NULL, 7},
    {&ai_commands[6], NULL, 0},
    {&ai_commands[7], &fork_begin, 42},
    {&ai_commands[8], NULL, 7},
    {&ai_commands[9], NULL, 7},
    {&ai_commands[10], NULL, 7},
    {&ai_commands[11], NULL, 0},
    {}
};

void free_ai_command(ai_command_t *ai_command)
{
    MY_FREE(ai_command->buffer);
    MY_FREE(ai_command);
}

ai_command_t *get_ai_command(zappy_server_t *zappy_server, char *buffer)
{
    ai_command_t *command = calloc(1, sizeof(*command));
    size_t len = 0;

    if (!command || !(command->buffer = strdup(buffer)))
        PERROR("Failed to allocate ai command", NULL);
    for (uint8_t i = 0; ai_command_time[i].command; ++i) {
        len = strlen(ai_command_time[i].command->mnemonique);
        if (!strncmp(ai_command_time[i].command->mnemonique, buffer, len) &&
            (!buffer[len] || strchr(WHITE_SPACES, buffer[len]) ||
            strchr(CRLF, buffer[len]))) {
            calculate_duration(&command->duration,
                ai_command_time[i].time_limit, zappy_server->freq);
            command->command_handler = ai_command_time[i].command;
            command->beging_handler = ai_command_time[i].beging_handler;
            break;
        }
    }
    return command;
}

void enqueue_command(zappy_server_t *zappy_server, client_t *client, char *buffer)
{
    tail_node_t *command_node = NULL;
    ai_command_t *command = NULL;

    if ((ZAPPY_CLIENT(client)->data.ai.nb_commands >= COMMAND_LIMIT) ||
        !(command = get_ai_command(zappy_server, buffer)))
        ERROR("Can not enqueue command",);
    if (TAILQ_EMPTY(&ZAPPY_CLIENT(client)->data.ai.commands)) {
        if (command->beging_handler &&
            !exec_command_begin(zappy_server, client, command))
            return free_ai_command(command);
        gettimeofday(&ZAPPY_CLIENT(client)->data.ai.command_timer, NULL);
    }
    if (!(command_node = malloc(sizeof(*command_node)))) {
        free_ai_command(command);
        ERROR("Failed to allocate commande ndoe memory",);
    }
    command_node->data = command;
    TAILQ_INSERT_TAIL(&ZAPPY_CLIENT(client)->data.ai.commands,
        command_node, entries);
    ++ZAPPY_CLIENT(client)->data.ai.nb_commands;
}

void handle_ai_command(zappy_server_t *zappy_server, client_t *client,
    const struct timeval *now)
{
    tail_node_t *command_node =
        TAILQ_FIRST(&AI_CLIENT(client)->commands);
    ai_command_t *ai_command = NULL;

    if (!command_node)
        return;
    ai_command = AI_COMMAND(command_node);
    if (!check_time_limit(&AI_CLIENT(client)->command_timer,
        &ai_command->duration, now)) {
        update_timeout(zappy_server,  &ai_command->duration);
        return;
    }
    TAILQ_REMOVE(&AI_CLIENT(client)->commands, command_node, entries);
    handle_command(zappy_server, client,
        ai_command->buffer, ai_commands);
    free_ai_command(ai_command);
    MY_FREE(command_node);
    --AI_CLIENT(client)->nb_commands;
    gettimeofday(&AI_CLIENT(client)->command_timer, NULL);
    handle_next_command_begin(zappy_server, client);
}
