/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** utils_rand
*/
#include "zappy_server.h"

void get_random_coord(int width, int height, coord_t *dest)
{
    dest->x = rand() % width;
    dest->y = rand() % height;
}

int get_random_int(int min, int max)
{
    int nb = rand() % (max - min + 1) + min;

    return (nb);
}

int get_random_direction(void)
{
    int direction = rand() % 4 + 1;

    return (direction);
}
