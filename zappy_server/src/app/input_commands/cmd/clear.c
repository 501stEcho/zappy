/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** clear
*/

#include <stdlib.h>

#include "zappy_server.h"
#include "protocol.h"
#include "infos.h"

void clear_command(zappy_server_t *zappy_server __attribute__((unused)),
    client_t *client __attribute__((unused)),
    command_t *command __attribute__((unused)))
{
    system("clear");
}
