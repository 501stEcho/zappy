/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** drones_creation
*/

#include "zappy_server.h"
#include "protocol.h"

node_t *create_drone(const coord_t *coords)
{
    node_t *drone_node = NULL;
    drone_t *new_drone = NULL;

    if (!(drone_node = malloc(sizeof(*drone_node))))
        PERROR("Drone memory allocation failed", NULL);
    if (!(new_drone = calloc(1, sizeof(*new_drone)))) {
        MY_FREE(drone_node);
        PERROR("Drone memory allocation failed", NULL);
    }
    new_drone->coords.x = (*coords).x;
    new_drone->coords.y = (*coords).y;
    new_drone->level = STRART_LEVEL;
    new_drone->direction = get_random_direction();
    drone_node->data = new_drone;
    return drone_node;
}
