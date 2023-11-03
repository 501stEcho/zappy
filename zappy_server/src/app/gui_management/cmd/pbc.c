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

static char *pbc(unsigned int id, char *message)
{
    char *response = NULL;

    asprintf(&response, GUI_PLAYER_BROADCAST " %d %s" CRLF, id, message);
    return response;
}

void pbc_all(zappy_server_t *infos, unsigned int id, char *message)
{
    char *response = pbc(id, message);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}
