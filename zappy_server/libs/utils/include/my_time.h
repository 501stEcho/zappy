/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** time
*/

#pragma once

#include <stdbool.h>
#include <sys/time.h>

#define MICRO_FACTOR 1000000

bool calculate_delta_time(struct timeval *result,
    const struct timeval *present, const struct timeval *past);
