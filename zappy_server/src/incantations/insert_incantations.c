/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** insert_incantation
*/

#include "zappy_server.h"
#include "protocol.h"
#include "gui.h"

bool insert_incantation(zappy_server_t *zappy_server,
    incantation_t *incantation)
{
    node_t *incantation_node = malloc(sizeof(*incantation_node));
    node_t *player_node = NULL;

    if (!incantation_node)
        return false;
    incantation_node->data = incantation;
    LIST_INSERT_HEAD(&zappy_server->incantations, incantation_node, entries);
    LIST_FOREACH(player_node, &incantation->players, entries) {
        AI_NODE(player_node)->incantating = true;
        enqueue_messages(&CLIENT(AI_NODE(player_node)->client)->communicator,
            WRITE, INCANTATION_START_MESSAGE CRLF, NULL);
    }
    pic_all(zappy_server, incantation);
    return true;
}
