/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** incantation
*/

#include "zappy_server.h"
#include "ai_messages.h"
#include "protocol.h"
#include "gui.h"
#include "ai.h"

static bool handle_incantation(zappy_server_t *zappy_server, client_t *client)
{
    incantation_t *incantation = create_incantation(zappy_server,
        AI_CLIENT(client)->drone->level, &AI_CLIENT(client)->drone->coords);

    if (!incantation)
        return false;
    if (!insert_incantation(zappy_server, incantation)) {
        free_list(&incantation->players, &free_incantating_player);
        MY_FREE(incantation);
        return false;
    }
    return true;
}

void incantation_cmd(zappy_server_t *zappy_server,
    client_t *client, command_t *command __attribute__((unused)))
{
    if (!handle_incantation(zappy_server, client))
        return enqueue_messages(&client->communicator,
            WRITE, AI_KO CRLF, NULL);
}
