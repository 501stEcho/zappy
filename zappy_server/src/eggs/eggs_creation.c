/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** eggs_creation
*/

#include "zappy_server.h"

tail_node_t *create_egg(zappy_server_t *zappy_server,
    const coord_t *coords, ssize_t parent_id)
{
    tail_node_t *egg_node = NULL;
    egg_t *new_egg = NULL;
    static size_t egg_id = 0;

    if (!(egg_node = malloc(sizeof(*egg_node))))
        PERROR("Drone memory allocation failed", NULL);
    if (!(new_egg = malloc(sizeof(*new_egg)))) {
        MY_FREE(egg_node);
        PERROR("Drone memory allocation failed", NULL);
    }
    new_egg->egg_id = egg_id++;
    new_egg->parent_id = parent_id;
    new_egg->coords.x = (*coords).x;
    new_egg->coords.y = (*coords).y;
    new_egg->is_mature = false;
    calculate_duration(&new_egg->incubation_duration,
        INCUBATION_TIME, zappy_server->freq);
    gettimeofday(&new_egg->incubation_timer, NULL);
    egg_node->data = new_egg;
    return egg_node;
}
