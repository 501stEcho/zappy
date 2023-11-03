/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** fork
*/

#include "zappy_server.h"
#include "ai_messages.h"
#include "protocol.h"
#include "gui.h"
#include "ai.h"

bool fork_begin(zappy_server_t *zappy_server,
    client_t *client, command_t *command)
{
    if (command->nb_segments != 1)
        return false;
    pfk_all(zappy_server, AI_CLIENT(client)->player_id);
    return true;
}

static bool handle_fork(zappy_server_t *zappy_server, client_t *client)
{
    egg_t *egg = new_egg(zappy_server, AI_CLIENT(client)->team,
        &AI_CLIENT(client)->drone->coords, AI_CLIENT(client)->player_id);

    if (!egg)
        return false;
    enw_all(zappy_server, egg);
    return true;
}

void fork_cmd(zappy_server_t *zappy_server,
    client_t *client, command_t *command __attribute__((unused)))
{
    if (handle_fork(zappy_server, client))
        enqueue_messages(&client->communicator,
            WRITE, AI_OK CRLF, NULL);
    else
        enqueue_messages(&client->communicator,
            WRITE, AI_KO CRLF, NULL);
}
