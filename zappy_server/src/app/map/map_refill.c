/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** map_refill
*/

#include "zappy_server.h"

void rand_ressources(zappy_server_t *infos,
map_t *map, ressources_t ressource, int nb_ressources)
{
    int x = 0;
    int y = 0;

    if (nb_ressources <= 0)
        return;
    for (int i = 0; i < nb_ressources; i++) {
        x = rand() % map->width;
        y = rand() % map->height;
        add_ressources_to_tile(infos, &map->tiles[y][x], 1, ressource);
    }
}

void refill_first_part(
zappy_server_t *infos, map_t *map)
{
    int nb_food = (map->width * map->height) * ressource_density[FOOD] -
    infos->global_inventory->food;
    int nb_linemate =
    (map->width * map->height) * ressource_density[LINEMATE] -
    infos->global_inventory->linemate;
    int nb_deraumere =
    (map->width * map->height) * ressource_density[DERAUMERE] -
    infos->global_inventory->deraumere;

    rand_ressources(infos, map, FOOD, nb_food);
    rand_ressources(infos, map, LINEMATE, nb_linemate);
    rand_ressources(infos, map, DERAUMERE, nb_deraumere);
}

void refill_second_part(
zappy_server_t *infos, map_t *map)
{
    int nb_sibur = (map->width * map->height) * ressource_density[SIBUR] -
    infos->global_inventory->sibur;
    int nb_mendiane =
    (map->width * map->height) * ressource_density[MENDIANE] -
    infos->global_inventory->mendiane;
    int nb_phiras = (map->width * map->height) * ressource_density[PHIRAS] -
    infos->global_inventory->phiras;
    int nb_thystame =
    (map->width * map->height) * ressource_density[THYSTAME] -
    infos->global_inventory->thystame;

    rand_ressources(infos, map, SIBUR, nb_sibur);
    rand_ressources(infos, map, MENDIANE, nb_mendiane);
    rand_ressources(infos, map, PHIRAS, nb_phiras);
    rand_ressources(infos, map, THYSTAME, nb_thystame);
}

void refill_map(zappy_server_t *infos, map_t *map)
{
    refill_first_part(infos, map);
    refill_second_part(infos, map);
}
