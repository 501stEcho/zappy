/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** new_client
*/

#include "protocol.h"
#include "zappy_server.h"

void send_greeting(client_t *client)
{
    enqueue_messages(&client->communicator, WRITE, GREETING CRLF, NULL);
}

void handle_client_type(zappy_server_t *zappy_server,
    node_t *client, char *command)
{
    node_t *entry = NULL;

    if (!strcmp(command, GRAPHIC_CMD))
        return handle_new_gui_client(zappy_server, client);
    LIST_FOREACH(entry, &zappy_server->teams, entries) {
        if (!strcmp(command, TEAM(entry)->name))
            return handle_new_ai_client(zappy_server, client, TEAM(entry));
    }
    enqueue_messages(&CLIENT(client)->communicator, WRITE, KO CRLF, NULL);
}

void send_clients(zappy_server_t *zappy_server, ...)
{
    node_t *entry = NULL;
    va_list args;
    va_list tmp;

    va_start(args, zappy_server);
    LIST_FOREACH(entry, &zappy_server->server.clients, entries) {
        va_copy(tmp, args);
        v_enqueue_messages(&CLIENT(entry)->communicator, WRITE, tmp);
    }
    va_end(args);
}
