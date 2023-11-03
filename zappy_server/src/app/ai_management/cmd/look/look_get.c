/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** look_get
*/
#include "ai.h"
#include "protocol.h"
#include "zappy_server.h"

int get_nb_players(int x, int y, zappy_server_t *server)
{
    int nb_players = 0;

    node_t *tmp_cli = NULL;

    LIST_FOREACH(tmp_cli, &server->players, entries) {
        if (AI(tmp_cli)->drone->coords.x == x &&
        AI(tmp_cli)->drone->coords.y == y)
            nb_players++;
    }
    return nb_players;
}

int get_nb_eggs(int x, int y, zappy_server_t *server)
{
    int nb_eggs = 0;
    node_t *team_entry = NULL;
    tail_node_t *egg_entry = NULL;

    LIST_FOREACH(team_entry, &server->teams, entries)
        TAILQ_FOREACH(egg_entry, &TEAM(team_entry)->eggs, entries)
            if (EGG(egg_entry)->coords.x == x && EGG(egg_entry)->coords.y == y)
                nb_eggs++;
    return nb_eggs;
}
