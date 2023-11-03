/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** time_management
*/

#include "zappy_server.h"
#include "protocol.h"
#include "ai.h"

bool check_time_limit(struct timeval *timer, struct timeval *duration,
    const struct timeval *now)
{
    struct timeval delta = {};
    struct timeval old_duration = *duration;

    calculate_delta_time(&delta, now, timer);
    if (calculate_delta_time(duration, &old_duration, &delta) ||
        (!duration ->tv_sec && !duration->tv_usec))
        return true;
    *timer = *now;
    return false;
}

void update_timeout(zappy_server_t *zappy_server,
    const struct timeval *duration)
{
    if (!zappy_server->time_out_needed) {
        zappy_server->time_out_needed = true;
        zappy_server->timeout = *duration;
        return;
    }
    if (zappy_server->timeout.tv_sec > duration->tv_sec)
        zappy_server->timeout = *duration;
    if (zappy_server->timeout.tv_sec == duration->tv_sec &&
        zappy_server->timeout.tv_usec > duration->tv_usec)
        zappy_server->timeout.tv_usec = duration->tv_usec;
}

void calculate_duration(struct timeval *dest,
    uint16_t time_limit, uint16_t freq)
{
    double microseconds = 0.0;

    microseconds = ((double)time_limit / (double)(freq)) * MICRO_FACTOR;
    dest->tv_sec = microseconds / MICRO_FACTOR;
    dest->tv_usec = (suseconds_t)microseconds % MICRO_FACTOR;
}
