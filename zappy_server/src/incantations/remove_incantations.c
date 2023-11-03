/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** remove_incantation
*/

#include "zappy_server.h"

void remove_from_incantations(zappy_server_t *zappy_server, ai_t *ai)
{
    node_t *incantation_entry = NULL;
    node_t *current = NULL;
    node_t *entry = NULL;

    LIST_FOREACH(incantation_entry, &zappy_server->incantations, entries) {
        entry = LIST_FIRST(&INCANTATION(incantation_entry)->players);
        while (entry) {
            current = entry;
            entry = LIST_NEXT(entry, entries);
            if (AI_NODE(current)->player_id == ai->player_id) {
                LIST_REMOVE(current, entries);
                MY_FREE(current);
            }
        }
    }
}
