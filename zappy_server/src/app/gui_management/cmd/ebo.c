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

static char *ebo(int id)
{
    char *response = NULL;

    asprintf(&response, GUI_EGG_CONNECTION " %d" CRLF, id);
    return response;
}

void ebo_all(zappy_server_t *infos, int id)
{
    char *response = ebo(id);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}
