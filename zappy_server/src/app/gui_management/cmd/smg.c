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

static char *smg(char *message)
{
    char *response = NULL;

    asprintf(&response, GUI_SERVER_MESSAGE " %s" CRLF, message);
    return response;
}

void smg_all(zappy_server_t *infos, char *message)
{
    char *response = smg(message);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}
