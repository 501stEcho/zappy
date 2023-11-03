/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** quit
*/

#include "zappy_server.h"
#include "protocol.h"

void quit_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command __attribute__((unused)))
{
    zappy_server->server.running = false;
}
