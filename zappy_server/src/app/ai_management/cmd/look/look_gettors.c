/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** look_gettors
*/

#include "ai.h"
#include "protocol.h"
#include "zappy_server.h"

char *get_look_response_south(zappy_server_t *server, coord_t coord, int level)
{
    char *response = NULL;
    char *tmp = NULL;
    inventory_t **map = server->map->tiles;
    response = append_str(response, "[", 0);
    for (int y = 0; y < level + 1; y++) {
        int ry =
        coord.y - y < 0 ? coord.y - y + server->map->height : coord.y - y;
        for (int x = y; x >= -y; x--) {
            int rx =
            coord.x + x < 0 ? coord.x + x + server->map->width : coord.x + x;
            rx = rx >= server->map->width ? rx - server->map->width : rx;
            tmp = get_tile_inventory(&map[ry][rx], rx, ry, server);
            response = append_str(response, tmp, 0);
            free(tmp);
        }
    }
    response[strlen(response) - 1] = '\0';
    return append_str(response, "]", 0);
}

char *get_look_response_west(zappy_server_t *server, coord_t coord, int level)
{
    char *response = NULL;
    char *tmp = NULL;
    inventory_t **map = server->map->tiles;
    response = append_str(response, "[", 0);
    for (int y = 0; y < level + 1; y++) {
        int ry = (coord.x - y) % server->map->width;
        ry = ry < 0 ? ry + server->map->width : ry;
        for (int x = -y; x <= y; x++) {
            int rx =
            coord.y + x < 0 ? coord.y + x + server->map->height : coord.y + x;
            rx = rx >= server->map->height ? rx - server->map->height : rx;
            tmp = get_tile_inventory(&map[rx][ry], ry, rx, server);
            response = append_str(response, tmp, 0);
            free(tmp);
        }
    }
    response[strlen(response) - 1] = '\0';
    return append_str(response, "]", 0);
}

char *get_look_response_north(zappy_server_t *server, coord_t coord, int level)
{
    char *response = NULL;
    char *tmp = NULL;
    inventory_t **map = server->map->tiles;
    response = append_str(response, "[", 0);
    for (int y = 0; y < level + 1; y++) {
        int ry = coord.y + y >= server->map->height
        ? coord.y + y - server->map->height
        : coord.y + y;
        ry = ry < 0 ? ry + server->map->height : ry;
        for (int x = -y; x <= y; x++) {
            int rx =
            coord.x + x < 0 ? coord.x + x + server->map->width : coord.x + x;
            rx = rx >= server->map->width ? rx - server->map->width : rx;
            tmp = get_tile_inventory(&map[ry][rx], rx, ry, server);
            response = append_str(response, tmp, 0);
            free(tmp);
        }
    }
    response[strlen(response) - 1] = '\0';
    return append_str(response, "]", 0);
}

char *get_look_response_east(zappy_server_t *server, coord_t coord, int level)
{
    char *response = NULL;
    char *tmp = NULL;
    inventory_t **map = server->map->tiles;
    response = append_str(response, "[", 0);
    for (int y = 0; y < level + 1; y++) {
        int ry = (coord.x + y) % server->map->width;
        for (int x = y; x >= -y; x--) {
            int rx =
            coord.y + x < 0 ? coord.y + x + server->map->height : coord.y + x;
            rx = rx >= server->map->height ? rx - server->map->height : rx;
            tmp = get_tile_inventory(&map[rx][ry], ry, rx, server);
            response = append_str(response, tmp, 0);
            free(tmp);
        }
    }
    response[strlen(response) - 1] = '\0';
    return append_str(response, "]", 0);
}
