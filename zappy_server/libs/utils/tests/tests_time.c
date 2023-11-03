/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** tests_time
*/

#include <criterion/criterion.h>

#include "my_time.h"

Test(time_tests, delta_time)
{
    struct timeval present = {.tv_sec = 1, .tv_usec = 0};
    struct timeval past = {.tv_sec = 0, .tv_usec = 0};
    struct timeval result = {};

    cr_assert_eq(calculate_delta_time(&result, &present, &past), 0);
    cr_assert_eq(result.tv_sec, 1);
    cr_assert_eq(result.tv_usec, 0);
    present.tv_sec = 0;
    past.tv_usec = 1;
    cr_assert_eq(calculate_delta_time(&result, &present, &past), 1);
}
