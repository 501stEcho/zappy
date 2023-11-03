/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** eject_eggs
*/

#include "zappy_server.h"
#include "protocol.h"
#include "gui.h"
#include "ai.h"

static bool eject_team_eggs(zappy_server_t *zappy_server, team_t *team,
    uint8_t x, uint8_t y)
{
    bool status = false;
    tail_node_t *current = NULL;
    tail_node_t *entry = NULL;

    entry = TAILQ_FIRST(&team->eggs);
    while (entry) {
        current = entry;
        entry = TAILQ_NEXT(entry, entries);
        if (EGG(current)->coords.x == x && EGG(current)->coords.y == y) {
            TAILQ_REMOVE(&team->eggs, current, entries);
            edi_all(zappy_server, EGG(current)->egg_id);
            team->nb_matures_eggs -= EGG(current)->is_mature ? 1 : 0;
            MY_FREE(current->data);
            MY_FREE(current);
            status = true;
        }
    }
    return status;
}

bool eject_eggs(zappy_server_t *zappy_server, client_t *client)
{
    bool status = false;
    node_t *entry = NULL;
    uint8_t x = AI_CLIENT(client)->drone->coords.x;
    uint8_t y = AI_CLIENT(client)->drone->coords.y;

    LIST_FOREACH(entry, &zappy_server->teams, entries)
        if (eject_team_eggs(zappy_server, TEAM(entry), x, y))
            status = true;
    return status;
}
