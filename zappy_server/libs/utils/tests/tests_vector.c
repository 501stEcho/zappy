/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** tests_vector
*/

#include <criterion/criterion.h>

#include "vector.h"

Test(vector, creation)
{
    vectot_t test_vector = new_vector(1.0, 2.0, 1.0, 1.0);

    cr_assert_eq(test_vector.x, 0.0);
    cr_assert_eq(test_vector.y, -1.0);
}

Test(vector, norme)
{
    vectot_t test_vector = {.x = 2.0, .y = 3.0};
    double norme = norme_vector(&test_vector);

    cr_assert_eq(norme, sqrt(13.0));
}

Test(vector, euclidian_distance)
{
    double distance = euclidian_distance(0.1, 0.0, 0.5, 1.2);

    cr_assert_eq(distance, sqrt(0.4 * 0.4 + 1.2 * 1.2));
}
