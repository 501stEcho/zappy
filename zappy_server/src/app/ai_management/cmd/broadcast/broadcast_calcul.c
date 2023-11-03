/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** broadcast_calcul
*/

#include "zappy_server.h"
#include "protocol.h"
#include "ai.h"

void get_coords_possibilities(zappy_server_t *zappy_server,
    const drone_t *drone, coord_t (*possibilities)[8])
{
    (*possibilities)[0].x = drone->coords.x - zappy_server->map->width;
    (*possibilities)[0].y = drone->coords.y;
    (*possibilities)[1].x = drone->coords.x + zappy_server->map->width;
    (*possibilities)[1].y = drone->coords.y;
    (*possibilities)[2].x = drone->coords.x;
    (*possibilities)[2].y = drone->coords.y - zappy_server->map->height;
    (*possibilities)[3].x = drone->coords.x;
    (*possibilities)[3].y = drone->coords.y + zappy_server->map->height;
    (*possibilities)[4].x = drone->coords.x - zappy_server->map->width;
    (*possibilities)[4].y = drone->coords.y - zappy_server->map->height;
    (*possibilities)[5].x = drone->coords.x + zappy_server->map->width;
    (*possibilities)[5].y = drone->coords.y + zappy_server->map->height;
    (*possibilities)[6].x = drone->coords.x + zappy_server->map->width;
    (*possibilities)[6].y = drone->coords.y - zappy_server->map->height;
    (*possibilities)[7].x = drone->coords.x - zappy_server->map->width;
    (*possibilities)[7].y = drone->coords.y + zappy_server->map->height;
}

vectot_t get_direction_vector(direction_t direction)
{
    vectot_t result = {};

    switch (direction) {
        case NORTH:
            result.y = 1.0;
            break;
        case EAST:
            result.x = 1.0;
            break;
        case SOUTH:
            result.y = -1.0;
            break;
        case WEST:
            result.x = -1.0;
            break;
    }
    return result;
}

int get_message_receive_direction(double angle)
{
    double half_small_angle = HALF_SMALL_ANGLE;
    double small_angle = SMALL_ANGLE;
    double big_angle = BIG_ANGLE;
    double radian_circle = RADIAN_CIRCLE;
    double begin = radian_circle - half_small_angle;
    double end = half_small_angle;

    for (uint8_t i = 1; i <= 8; ++i) {
        if ((begin <= angle) && (angle <= end))
            return i;
        begin = end;
        if (i % 2)
            end += big_angle;
        else
            end += small_angle;
    }
    return 1;
}
