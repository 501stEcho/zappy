/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** free_ais
*/

#include "zappy_server.h"
#include "command.h"
#include "ai.h"

static void free_ai_commands(tail_node_t *node)
{
    if (node->data)
        free_ai_command(AI_COMMAND(node));
    MY_FREE(node);
}

void free_ai(node_t *ai_node)
{
    if (AI(ai_node)->client) {
        LIST_REMOVE(AI(ai_node)->client, entries);
        close_client(AI(ai_node)->client);
    }
    if (AI(ai_node)->team)
        --AI(ai_node)->team->nb_drones;
    free_tail(&AI(ai_node)->commands, &free_ai_commands);
    LIST_REMOVE(ai_node, entries);
    MY_FREE(ai_node->data);
    MY_FREE(ai_node);
}

void free_ais(head_t *ais)
{
    free_list(ais, &free_ai);
}
