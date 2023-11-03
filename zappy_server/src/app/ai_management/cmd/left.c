/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** left
*/

#include "zappy_server.h"
#include "ai_messages.h"
#include "protocol.h"
#include "gui.h"
#include "ai.h"

void left_cmd(zappy_server_t *server __attribute__((unused)),
    client_t*client, command_t *cmd __attribute__((unused)))
{
    switch (AI_CLIENT(client)->drone->direction) {
        case NORTH:
            AI_CLIENT(client)->drone->direction = WEST;
            break;
        case EAST:
            AI_CLIENT(client)->drone->direction = NORTH;
            break;
        case SOUTH:
            AI_CLIENT(client)->drone->direction = EAST;
            break;
        case WEST:
            AI_CLIENT(client)->drone->direction = SOUTH;
            break;
    }
    enqueue_messages(&client->communicator, WRITE,
        AI_OK CRLF, NULL);
    ppo_all(server, AI_CLIENT(client)->player_id);
}
