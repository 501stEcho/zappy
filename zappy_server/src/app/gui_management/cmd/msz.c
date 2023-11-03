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

static char *msz(zappy_server_t* infos)
{
    char *response = NULL;

    asprintf(&response, GUI_MAP_SIZE " %d %d" CRLF,
        infos->map->width, infos->map->height);
    return response;
}

void msz_event(zappy_server_t* infos, client_t *client)
{
    char *response = msz(infos);

    enqueue_messages(&client->communicator, WRITE, response, NULL);
    MY_FREE(response);
}

void msz_cmd(zappy_server_t *infos, client_t *client,
    command_t *command __attribute__((unused)))
{
    msz_event(infos, client);
}
