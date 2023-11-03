/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** connect_nbr
*/

#include "zappy_server.h"
#include "protocol.h"
#include "ai.h"

void connect_nbr_cmd(zappy_server_t *zappy_server __attribute__((unused)),
    client_t *client, command_t *command __attribute__((unused)))
{
    char *response = NULL;

    asprintf(&response, "%hu" CRLF,
        AI_CLIENT(client)->team->nb_matures_eggs);
    enqueue_messages(&client->communicator, WRITE, response, NULL);
    MY_FREE(response);
}
