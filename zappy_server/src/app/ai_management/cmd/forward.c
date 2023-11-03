/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** forward
*/

#include "zappy_server.h"
#include "ai_messages.h"
#include "protocol.h"
#include "gui.h"
#include "ai.h"

static void forward_gestion(zappy_server_t *server, client_t *client)
{
    int x = AI_CLIENT(client)->drone->coords.x;
    int y = AI_CLIENT(client)->drone->coords.y;
    switch (AI_CLIENT(client)->drone->direction) {
    case NORTH:
        AI_CLIENT(client)->drone->coords.y =
        (y + 1 >= server->map->height) ? 0 : y + 1;
        break;
    case EAST:
        AI_CLIENT(client)->drone->coords.x =
        (x + 1 >= server->map->width) ? 0 : x + 1;
        break;
    case SOUTH:
            AI_CLIENT(client)->drone->coords.y =
        (y - 1 < 0) ? server->map->height - 1 : y - 1;
        break;
    case WEST:
        AI_CLIENT(client)->drone->coords.x =
        (x - 1 < 0) ? server->map->width - 1 : x - 1;
        break;
    }
}

void forward_cmd(zappy_server_t *server, client_t *client,
    command_t *cmd __attribute__((unused)))
{
    forward_gestion(server, client);
    enqueue_messages(&client->communicator,
        WRITE, AI_OK CRLF, NULL);
    ppo_all(server, AI_CLIENT(client)->player_id);
}
