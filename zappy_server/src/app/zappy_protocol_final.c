/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** zappy_protocol_final
*/

#include "zappy_server.h"
#include "protocol.h"
#include "gui.h"

static void spawn_eggs(zappy_server_t *zappy_server, team_t *team,
    const struct timeval *now)
{
    tail_node_t *entry = NULL;

    TAILQ_FOREACH(entry, &team->eggs, entries) {
        if (EGG(entry)->is_mature)
            continue;
        if (check_time_limit(&EGG(entry)->incubation_timer,
            &EGG(entry)->incubation_duration, now)) {
                EGG(entry)->is_mature = true;
                eht_all(zappy_server, EGG(entry));
                ++team->nb_matures_eggs;
        } else {
            gettimeofday(&EGG(entry)->incubation_timer, NULL);
            update_timeout(zappy_server, &EGG(entry)->incubation_duration);
        }
    }
}

static void respawn_eggs(zappy_server_t *zappy_server,
    const struct timeval *now)
{
    egg_t *egg = NULL;
    node_t *entry = NULL;
    coord_t coords = {};

    LIST_FOREACH(entry, &zappy_server->teams, entries) {
        spawn_eggs(zappy_server, TEAM(entry), now);
        for (uint32_t nb_drones = TEAM(entry)->nb_drones +
            TEAM(entry)->nb_matures_eggs;
            nb_drones < zappy_server->clients_nb; ++nb_drones) {
                get_random_coord(zappy_server->width,
                    zappy_server->height, &coords);
                egg = new_egg(zappy_server, TEAM(entry), &coords, -1);
                if (egg) {
                    egg->is_mature = true;
                    ++TEAM(entry)->nb_matures_eggs;
                    enw_all(zappy_server, egg);
                    eht_all(zappy_server, egg);
                }
        }
    }
}

static bool check_team_victory(team_t *team)
{
    uint16_t max_level_drones = 0;
    node_t *entry = NULL;

    LIST_FOREACH(entry, &team->drones, entries)
        if (DRONE(entry)->level == MAX_LEVEL)
            ++max_level_drones;
    if (max_level_drones >= MAX_LEVEL_WIN)
        return true;
    return false;
}

static bool check_victory(zappy_server_t *zappy_server,
    const struct timeval *now)
{
    node_t *entry = NULL;
    struct timeval game_duration = {};

    LIST_FOREACH(entry, &zappy_server->teams, entries)
        if (check_team_victory(TEAM(entry))) {
            zappy_server->state = END;
            all_ai_disconnection(zappy_server);
            seg_all(zappy_server, TEAM(entry)->name);
            calculate_delta_time(&game_duration, now,
                &zappy_server->game_timer);
            printf("Team %s as won\n"
                "The game ended in %ld seconds ans %ld microseconds\n",
                TEAM(entry)->name, game_duration.tv_sec, game_duration.tv_usec);
            return true;
        }
    return false;
}

void exec_zappy_protocol_final_checks(zappy_server_t *zappy_server,
    const struct timeval *now)
{
    if ((zappy_server->state != RUNNING) || check_victory(zappy_server, now))
        return;
    if (check_time_limit(&zappy_server->refill_timer,
        &zappy_server->refill_duration, now)) {
        refill_map(zappy_server, zappy_server->map);
        mct_all(zappy_server);
        calculate_duration(&zappy_server->refill_duration, REFILL_TIME,
            zappy_server->freq);
        gettimeofday(&zappy_server->refill_timer, NULL);
    }
    update_timeout(zappy_server, &zappy_server->refill_duration);
    respawn_eggs(zappy_server, now);
    handle_incantations(zappy_server, now);
}
