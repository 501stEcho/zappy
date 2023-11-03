/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** eht
*/

#include "zappy_server.h"
#include "gui_messages.h"
#include "protocol.h"
#include "gui.h"

static char *eht(const egg_t *egg)
{
    char *response = NULL;

    asprintf(&response, GUI_EGG_MATURATION " %ld" CRLF, egg->egg_id);
    return response;
}

void eht_event(client_t *client, const egg_t *egg)
{
    char *response = eht(egg);

    if (response) {
        enqueue_messages(&client->communicator, WRITE, response, NULL);
        MY_FREE(response);
    }
}

void eht_all(zappy_server_t *infos, const egg_t *egg)
{
    char *response = eht(egg);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}
