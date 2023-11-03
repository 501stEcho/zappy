/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** vector
*/

#pragma once

#include <math.h>

typedef struct vectot_s {
    double x;
    double y;
} vectot_t;

vectot_t new_vector(double a_x, double a_y, double b_x, double b_y);
double norme_vector(const vectot_t *vector);
double euclidian_distance(double a_x, double a_y, double b_x, double b_y);
