/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** zappy_protocol
*/

#include "zappy_server.h"
#include "protocol.h"

void exec_zappy_protocol(zappy_server_t *zappy_server,
    const struct timeval *now)
{
    node_t *current = NULL;
    node_t *entry = NULL;
    char *buffer = NULL;

    handle_input_command(zappy_server);
    entry = LIST_FIRST(&zappy_server->server.clients);
    while (entry) {
        current = entry;
        entry = LIST_NEXT(entry, entries);
        if ((buffer = extract_until(&CLIENT(current)->communicator.read,
            CRLF)) && (zappy_server->state != LOADING)) {
            CLIENT(current)->data ?
                handle_user_command(zappy_server, CLIENT(current), buffer) :
                handle_unkown_user_command(zappy_server,
                    current, buffer);
        }
        MY_FREE(buffer);
    }
    handle_ai_protocol(zappy_server, now);
    exec_zappy_protocol_final_checks(zappy_server, now);
}
