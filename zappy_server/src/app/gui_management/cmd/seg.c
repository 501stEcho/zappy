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

static char *seg(const char *team_name)
{
    char *response = NULL;

    asprintf(&response, GUI_END_OF_GAME " %s" CRLF, team_name);
    return response;
}

void seg_all(zappy_server_t *infos, const char *tean_name)
{
    char *response = seg(tean_name);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}
