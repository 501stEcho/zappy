/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** free_ai
*/

#include "zappy_server.h"
#include "protocol.h"
#include "infos.h"
#include "ai.h"

void ai_disconnection(void *ai_node)
{
    node_t *disconnected_ai_node = ((node_t *)ai_node);

    if (AI(disconnected_ai_node)->client)
        display_client(CLIENT(AI(disconnected_ai_node)->client));
    else
        printf("No clients\n");
    AI(disconnected_ai_node)->client = NULL;
    AI(disconnected_ai_node)->alive = false;
}

void ai_node_disconnection(node_t *ai_node)
{
    if (AI(ai_node)->client) {
        LIST_REMOVE(AI(ai_node)->client, entries);
        close_client(AI(ai_node)->client);
        AI(ai_node)->client = NULL;
    }
    AI(ai_node)->alive = false;
}

void all_ai_disconnection(zappy_server_t *zappy_server)
{
    apply_list(&zappy_server->players, &ai_node_disconnection);
}
