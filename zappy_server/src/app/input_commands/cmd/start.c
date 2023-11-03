/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** start
*/

#include "zappy_server.h"
#include "protocol.h"

void start_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command __attribute__((unused)))
{
    switch (zappy_server->state) {
        case RUNNING:
        case PAUSE:
            printf("Can't start the game because it's already running\n");
            return;
        case LOADING:
            printf("Starting the game\n");
            send_clients(zappy_server, GREETING CRLF, NULL);
            zappy_server->server.connection_handler = &send_greeting;
            zappy_server->state = RUNNING;
            return;
        case END:
            printf("Can't start the game because the game is over\n");
            return;
    }
    zappy_server->server.running = false;
}
