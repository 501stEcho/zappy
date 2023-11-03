/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** timer_management
*/

#include "zappy_server.h"
#include "protocol.h"
#include "ai.h"

static void update_incubation_timers(zappy_server_t *zappy_server,
    const struct timeval *now)
{
    tail_node_t *egg_entry = NULL;
    node_t *team_entry = NULL;

    LIST_FOREACH(team_entry, &zappy_server->teams, entries)
        TAILQ_FOREACH(egg_entry, &TEAM(team_entry)->eggs, entries) {
            if (EGG(egg_entry)->is_mature)
                continue;
            EGG(egg_entry)->incubation_timer = *now;
        }
}

static void update_incantation_timers(zappy_server_t *zappy_server,
    const struct timeval *now)
{
    node_t *entry = NULL;

    LIST_FOREACH(entry, &zappy_server->incantations, entries)
        INCANTATION(entry)->timer = *now;
}

static void update_ai_timers(zappy_server_t *zappy_server,
    const struct timeval *now)
{
    node_t *entry = NULL;

    LIST_FOREACH(entry, &zappy_server->players, entries) {
        AI(entry)->food_timer = *now;
        AI(entry)->command_timer = *now;
    }
}

void update_all_timers(zappy_server_t *zappy_server,
    const struct timeval *now)
{
    update_incubation_timers(zappy_server, now);
    update_incantation_timers(zappy_server, now);
    update_ai_timers(zappy_server, now);
    zappy_server->refill_timer = *now;
    return;
}
