/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** vector
*/

#include "vector.h"

vectot_t new_vector(double a_x, double a_y, double b_x, double b_y)
{
    vectot_t new = {.x = b_x - a_x, .y = b_y - a_y};

    return new;
}

double norme_vector(const vectot_t *vector)
{
    return sqrt(vector->x * vector->x + vector->y * vector->y);
}

double euclidian_distance(double a_x, double a_y, double b_x, double b_y)
{
    double x = b_x - a_x;
    double y = b_y - a_y;

    return sqrt(x * x + y * y);
}
