/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** map_inventory_gestion
*/

#include "zappy_server.h"

void create_map(zappy_server_t *infos, int width, int height)
{
    map_t *map = calloc(1, sizeof(map_t));
    infos->global_inventory = calloc(1, sizeof(inventory_t));

    if (!map)
        return;
    map->width = width;
    map->height = height;
    if (!(map->tiles = calloc(height + 1, sizeof(inventory_t *))))
        return;
    for (int i = 0; i < height; i++) {
        if (!(map->tiles[i] = calloc(width + 1, sizeof(inventory_t))))
            return;
    }
    infos->map = map;
    refill_map(infos, map);
}

void print_map(map_t *map)
{
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            printf("Tile: [%d][%d]\n", i, j);
            printf("Food: %d\nLinemate: %d\nDeraumere: %d\n",
            map->tiles[i][j].food, map->tiles[i][j].linemate,
            map->tiles[i][j].deraumere);
            printf("Sibur: %d\nMendiane: %d\nPhiras: %d\nThystame: %d\n",
            map->tiles[i][j].sibur, map->tiles[i][j].mendiane,
            map->tiles[i][j].phiras, map->tiles[i][j].thystame);
            printf("<======>\n");
        }
        printf("<==============>\n");
    }
}

void free_map(map_t *map)
{
    for (int i = 0; i < map->height; i++)
        free(map->tiles[i]);
    free(map->tiles);
    free(map);
}

void remove_ressources(zappy_server_t *zappy_server, const coord_t *coords,
    const inventory_t *ressouces)
{
    zappy_server->map->tiles[coords->y][coords->x].linemate -=
        ressouces->linemate;
    zappy_server->global_inventory->linemate -= ressouces->linemate;
    zappy_server->map->tiles[coords->y][coords->x].deraumere -=
        ressouces->deraumere;
    zappy_server->global_inventory->deraumere -= ressouces->deraumere;
    zappy_server->map->tiles[coords->y][coords->x].sibur -=
        ressouces->sibur;
    zappy_server->global_inventory->sibur -= ressouces->sibur;
    zappy_server->map->tiles[coords->y][coords->x].mendiane -=
        ressouces->mendiane;
    zappy_server->global_inventory->mendiane -= ressouces->mendiane;
    zappy_server->map->tiles[coords->y][coords->x].phiras -=
        ressouces->phiras;
    zappy_server->global_inventory->phiras -= ressouces->phiras;
    zappy_server->map->tiles[coords->y][coords->x].thystame -=
        ressouces->thystame;
    zappy_server->global_inventory->thystame -= ressouces->thystame;
}
