/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** msz
*/

#include "zappy_server.h"
#include "gui_messages.h"
#include "protocol.h"
#include "gui.h"

static char *pgt(int id, ressources_t ressource)
{
    char *response = NULL;

    asprintf(&response, GUI_PLAYER_COLLECTING " %d %d" CRLF, id, ressource);
    return response;
}

void pgt_all(zappy_server_t *infos, int id, ressources_t ressource)
{
    char *response = pgt(id, ressource);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}
