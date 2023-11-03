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

static char *pex(unsigned int id)
{
    char *response = NULL;

    asprintf(&response, GUI_PLAYER_EJECTION " %d" CRLF, id);
    return response;
}

void pex_all(zappy_server_t *infos, unsigned int id)
{
    char *response = pex(id);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}
