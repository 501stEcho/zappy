/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** msz
*/

#include "zappy_server.h"
#include "protocol.h"
#include "gui.h"

void mct_event(zappy_server_t *infos, client_t *client)
{
    for (int x = 0; x < infos->map->width; x++)
        for (int y = 0; y < infos->map->height; y++)
            bct_event(infos, client, x, y);
}

void mct_all(zappy_server_t *infos)
{
    for (int x = 0; x < infos->map->width; x++)
        for (int y = 0; y < infos->map->height; y++)
            bct_all(infos, x, y);
}

void mct_cmd(zappy_server_t *infos, client_t *client,
    command_t *cmd __attribute__((unused)))
{
    mct_event(infos, client);
}
