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

static char *pie(int x, int y, bool result)
{
    char *response = NULL;

    asprintf(&response, GUI_PLAYER_INCANTATION_END " %d %d %d" CRLF,
        x, y, result);
    return response;
}

void pie_all(zappy_server_t *infos, int x, int y, bool result)
{
    char *response = pie(x, y, result);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}
