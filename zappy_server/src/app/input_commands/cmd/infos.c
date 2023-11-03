/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** infos
*/

#include "protocol.h"
#include "infos.h"
#include "gui.h"

void map_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command __attribute__((unused)))
{
    print_map(zappy_server->map);
}
