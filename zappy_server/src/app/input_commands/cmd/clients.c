/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** clients
*/

#include "zappy_server.h"
#include "protocol.h"
#include "infos.h"
#include "gui.h"

void clients_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command __attribute__((unused)))
{
    apply_clients(&zappy_server->server.clients, &display_client);
}

void send_ais_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command)
{
    send_ais(zappy_server, command->segments[1], CRLF, NULL);
}

void send_guis_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command)
{
    smg_all(zappy_server, command->segments[1]);
}
