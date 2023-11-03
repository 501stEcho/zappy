/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** incantations_creation
*/

#include "zappy_server.h"
#include "protocol.h"

static bool insert_player(incantation_t *incantation, ai_t *ai)
{
    node_t *player_node = NULL;

    if (!(player_node = malloc(sizeof(*player_node))))
        return false;
    player_node->data = ai;
    LIST_INSERT_HEAD(&incantation->players, player_node, entries);
    return true;
}

static uint16_t get_incantating_player(zappy_server_t *zappy_server,
    incantation_t *incantation)
{
    node_t *entry = NULL;
    uint16_t nb_players = 0;

    LIST_FOREACH(entry, &zappy_server->players, entries)
        if (AI(entry)->alive && AI(entry)->client && !AI(entry)->incantating &&
            AI(entry)->drone->level == incantation->level &&
            AI(entry)->drone->coords.x == incantation->coords.x &&
            AI(entry)->drone->coords.y == incantation->coords.y)
                if (insert_player(incantation, AI(entry)))
                    ++nb_players;
    return nb_players;
}

incantation_t *create_incantation(zappy_server_t *zappy_server,
    uint8_t level, const coord_t *coords)
{
    incantation_t *new = NULL;

    if ((level > (MAX_LEVEL - 1)) ||
        (!check_required_ressourcies(zappy_server,
        &incantation_requirements[level - 1], coords)) ||
        !(new = malloc(sizeof(*new))))
        ERROR("Failed to create new incantation", NULL);
    LIST_INIT(&new->players);
    new->level = level;
    new->coords.x = (*coords).x;
    new->coords.y = (*coords).y;
    if (get_incantating_player(zappy_server, new) <
        incantation_requirements[level - 1].nb_playes) {
        free_list(&new->players, &free_incantating_player);
        MY_FREE(new);
        ERROR("Required number of player is not present", NULL);
    }
    calculate_duration(&new->duration, INCANTATION_TIME, zappy_server->freq);
    gettimeofday(&new->timer, NULL);
    return new;
}
