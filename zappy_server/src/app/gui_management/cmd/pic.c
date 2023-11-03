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

static char *pic(const incantation_t *incantation)
{
    char *response = NULL;
    char *tmp = NULL;
    node_t *entry = NULL;

    asprintf(&response, GUI_PLAYER_INCANTATION_START " %d %d %d",
        incantation->coords.x, incantation->coords.y, incantation->level);
    LIST_FOREACH(entry, &incantation->players, entries) {
        asprintf(&tmp, "%s %ld", response, AI_NODE(entry)->player_id);
        MY_FREE(response);
        response = tmp;
    }
    asprintf(&tmp, "%s" CRLF, response);
    MY_FREE(response);
    response = tmp;
    return response;
}

void pic_all(zappy_server_t *infos, const incantation_t *incantation)
{
    char *response = pic(incantation);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}
