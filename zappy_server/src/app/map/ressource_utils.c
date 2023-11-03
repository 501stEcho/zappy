/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ressource_utils
*/
#include "zappy_server.h"

void add_ressources_to_tile_bis(zappy_server_t *infos,
inventory_t *map_tile, int nb, ressources_t ressource)
{
    if (ressource == MENDIANE) {
        map_tile->mendiane += nb;
        infos->global_inventory->mendiane += nb;
    }
    if (ressource == PHIRAS) {
        map_tile->phiras += nb;
        infos->global_inventory->phiras += nb;
    }
    if (ressource == THYSTAME) {
        map_tile->thystame += nb;
        infos->global_inventory->thystame += nb;
    }
}

void add_ressources_to_tile(zappy_server_t *infos,
inventory_t *map_tile, int nb, ressources_t ressource)
{
    if (ressource == FOOD) {
        map_tile->food += nb;
        infos->global_inventory->food += nb;
    }
    if (ressource == LINEMATE) {
        map_tile->linemate += nb;
        infos->global_inventory->linemate += nb;
    }
    if (ressource == DERAUMERE) {
        map_tile->deraumere += nb;
        infos->global_inventory->deraumere += nb;
    }
    if (ressource == SIBUR) {
        map_tile->sibur += nb;
        infos->global_inventory->sibur += nb;
    }
    add_ressources_to_tile_bis(infos, map_tile, nb, ressource);
}

void remove_ressources_to_tile_bis(zappy_server_t *infos,
inventory_t *map_tile, int nb, ressources_t ressource)
{
    if (ressource == MENDIANE) {
        map_tile->mendiane -= nb;
        infos->global_inventory->mendiane -= nb;
    }
    if (ressource == PHIRAS) {
        map_tile->phiras -= nb;
        infos->global_inventory->phiras -= nb;
    }
    if (ressource == THYSTAME) {
        map_tile->thystame -= nb;
        infos->global_inventory->thystame -= nb;
    }
}

void remove_ressources_from_tile(zappy_server_t *infos,
inventory_t *map_tile, int nb, ressources_t ressource)
{
    if (ressource == FOOD) {
        map_tile->food -= nb;
        infos->global_inventory->food -= nb;
    }
    if (ressource == LINEMATE) {
        map_tile->linemate -= nb;
        infos->global_inventory->linemate -= nb;
    }
    if (ressource == DERAUMERE) {
        map_tile->deraumere -= nb;
        infos->global_inventory->deraumere -= nb;
    }
    if (ressource == SIBUR) {
        map_tile->sibur -= nb;
        infos->global_inventory->sibur -= nb;
    }
    remove_ressources_to_tile_bis(infos, map_tile, nb, ressource);
}
