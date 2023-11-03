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

static char *sgt(zappy_server_t *infos)
{
    char *response = NULL;

    asprintf(&response, GUI_GET_FREQUENCE " %hu" CRLF, infos->freq);
    return response;
}

void sgt_event(zappy_server_t *infos, client_t *client)
{
    char *response = sgt(infos);

    if (response)
        enqueue_messages(&client->communicator, WRITE, response, NULL);
    MY_FREE(response);
}

void sgt_all(zappy_server_t *infos)
{
    char *response = sgt(infos);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}

void sgt_cmd(zappy_server_t *infos, client_t *client,
    command_t *cmd __attribute__((unused)))
{
    sgt_event(infos, client);
}
