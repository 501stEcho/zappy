/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** time
*/

#include "my_time.h"

bool calculate_delta_time(struct timeval *result,
    const struct timeval *present, const struct timeval *past)
{
    struct timeval tmp = {.tv_sec = past->tv_sec, .tv_usec = past->tv_usec};
    int carry = 0;

    if (present->tv_usec < tmp.tv_usec) {
        carry = (tmp.tv_usec - present->tv_usec) / MICRO_FACTOR + 1;
        tmp.tv_usec -= MICRO_FACTOR * carry;
        tmp.tv_sec += carry;
    }
    if (present->tv_usec - tmp.tv_usec > MICRO_FACTOR) {
        carry = (present->tv_usec - tmp.tv_usec) / MICRO_FACTOR;
        tmp.tv_usec += MICRO_FACTOR * carry;
        tmp.tv_sec -= carry;
    }
    result->tv_sec = present->tv_sec - tmp.tv_sec;
    result->tv_usec = present->tv_usec - tmp.tv_usec;
    return present->tv_sec < tmp.tv_sec;
}
