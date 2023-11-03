/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** eject
*/

#include "zappy_server.h"
#include "ai_messages.h"
#include "protocol.h"
#include "gui.h"
#include "ai.h"

void eject_cmd(zappy_server_t *server, client_t *client,
    command_t *cmd __attribute__((unused)))
{
    bool eject_players_status = eject_players(server, client);
    bool eject_eggs_status = true;

    if (server->display_eggs)
        eject_eggs_status = eject_eggs(server, client);
    if (!eject_players_status && !eject_eggs_status)
        return enqueue_messages(&client->communicator,
            WRITE, AI_KO CRLF, NULL);
    enqueue_messages(&client->communicator,
        WRITE, AI_OK CRLF, NULL);
    pex_all(server, AI_CLIENT(client)->player_id);
}
