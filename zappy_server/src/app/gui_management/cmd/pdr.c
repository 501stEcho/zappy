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

static char *pdr(int id, ressources_t ressource)
{
    char *response = NULL;

    asprintf(&response, GUI_PLAYER_DROPPING " %d %d" CRLF, id, ressource);
    return response;
}

void pdr_all(zappy_server_t *infos, int id, ressources_t ressource)
{
    char *response = pdr(id, ressource);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}
