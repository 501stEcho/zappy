/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** free_guis
*/

#include "protocol.h"
#include "zappy_server.h"

static void free_gui_node(node_t *gui)
{
    MY_FREE(gui);
}

void free_guis(head_t *guis)
{

    free_list(guis, &free_gui_node);
}
