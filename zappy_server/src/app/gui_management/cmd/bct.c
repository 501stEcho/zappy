/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** msz
*/

#include "zappy_server.h"
#include "gui_messages.h"
#include "protocol.h"
#include "gui.h"

static char *bct(zappy_server_t *infos, int x, int y)
{
    char *response = NULL;

    asprintf(&response, GUI_TILE_CONTENT " %d %d %d %d %d %d %d %d %d" CRLF,
        x, y, infos->map->tiles[y][x].food, infos->map->tiles[y][x].linemate,
        infos->map->tiles[y][x].deraumere, infos->map->tiles[y][x].sibur,
        infos->map->tiles[y][x].mendiane, infos->map->tiles[y][x].phiras,
        infos->map->tiles[y][x].thystame);
    return response;
}

void bct_event(zappy_server_t *infos, client_t *client, int x, int y)
{
    char *response = bct(infos, x, y);

    if (response)
        enqueue_messages(&client->communicator, WRITE, response, NULL);
    MY_FREE(response);
}

void bct_all(zappy_server_t *infos, int x, int y)
{
    char *response = bct(infos, x, y);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}

void bct_cmd(zappy_server_t *infos, client_t *client, command_t *command)
{
    int x = -1;
    int y = -1;

    x = atoi(command->segments[1]);
    y = atoi(command->segments[2]);
    if (x < 0 || x >= infos->map->width || y < 0 || y >= infos->map->height)
        return sbp_event(client);
    bct_event(infos, client, x, y);
}
