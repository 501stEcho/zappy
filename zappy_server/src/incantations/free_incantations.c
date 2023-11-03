/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** free_incantations
*/

#include "zappy_server.h"
#include "protocol.h"

void free_incantating_player(node_t *player)
{
    MY_FREE(player);
}

static void free_incantation_node(node_t *incantation)
{
    free_list(&INCANTATION(incantation)->players, &free_incantating_player);
    MY_FREE(incantation->data);
    MY_FREE(incantation);
}

void free_incantations(zappy_server_t *zappy_server)
{
    free_list(&zappy_server->incantations, &free_incantation_node);
}
