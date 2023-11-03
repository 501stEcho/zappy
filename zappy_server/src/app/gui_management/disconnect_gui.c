/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** free_gui
*/

#include "infos.h"
#include "protocol.h"
#include "zappy_server.h"

void gui_disconnection(void *gui)
{
    node_t *to_free_node = ((node_t *)gui);
    zappy_client_t *to_free = ((zappy_client_t *)to_free_node->data);

    if (to_free->data.gui.client)
        display_client(CLIENT(to_free->data.gui.client));
    else
        printf("No clients\n");
    MY_FREE(to_free);
    LIST_REMOVE(to_free_node, entries);
    MY_FREE(to_free_node);
}
