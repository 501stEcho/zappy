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

static char *enw(const egg_t *egg)
{
    char *response = NULL;

    asprintf(&response, GUI_EGG_LAYED " %ld %ld %d %d" CRLF,
        egg->egg_id, egg->parent_id, egg->coords.x, egg->coords.y);
    return response;
}

void enw_event(client_t *client, const egg_t *egg)
{
    char *response = enw(egg);

    if (response) {
        enqueue_messages(&client->communicator, WRITE, response, NULL);
        MY_FREE(response);
    }
}

void enw_all(zappy_server_t *infos, const egg_t *egg)
{
    char *response = enw(egg);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}
