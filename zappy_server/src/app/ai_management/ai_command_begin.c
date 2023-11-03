/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** ai_command_begin
*/

#include "zappy_server.h"
#include "ai_messages.h"
#include "protocol.h"
#include "ai.h"

bool exec_command_begin(zappy_server_t *zappy_server,
    client_t *client, ai_command_t *ai_command)
{
    command_t *command = get_command(ai_command->buffer);

    if (!command ||
        ((command->nb_segments - 1) != ai_command->command_handler->nb_args)) {
        printf("[%s] : Invalid number of args, expected %hu but got %hu.\n",
        ai_command->command_handler->mnemonique,
            ai_command->command_handler->nb_args, command->nb_segments - 1);
        enqueue_messages(&client->communicator,
            WRITE, AI_KO CRLF, NULL);
        free_command(command);
        return false;
    }
    if (!ai_command->beging_handler(zappy_server, client, command)) {
        enqueue_messages(&client->communicator,
            WRITE, AI_KO CRLF, NULL);
        free_command(command);
        return false;
    }
    free_command(command);
    return true;
}

void handle_next_command_begin(zappy_server_t *zappy_server, client_t *client)
{
    tail_node_t *current = NULL;
    tail_node_t *entry = NULL;

    entry = TAILQ_FIRST(&AI_CLIENT(client)->commands);
    while (entry) {
        current = entry;
        entry = TAILQ_NEXT(entry, entries);
        if (AI_COMMAND(current)->beging_handler &&
            !exec_command_begin(zappy_server, client, AI_COMMAND(current))) {
            TAILQ_REMOVE(&AI_CLIENT(client)->commands, current, entries);
            free_ai_command(AI_COMMAND(current));
            MY_FREE(current);
        } else {
            return;
        }
    }
}
