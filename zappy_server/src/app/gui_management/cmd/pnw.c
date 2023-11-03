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

static char *pnw(ai_t *player)
{
    char *response = NULL;

    asprintf(&response, GUI_PLAYER_CONNEXION " %ld %d %d %d %d %s" CRLF,
        player->player_id,
        player->drone->coords.x, player->drone->coords.y,
        player->drone->direction, player->drone->level,
        player->team->name);
    return response;
}

void pnw_event(ai_t *player, client_t *client)
{
    char *response = pnw(player);

    if (response) {
        enqueue_messages(&client->communicator, WRITE, response, NULL);
        MY_FREE(response);
    }
}

void pnw_all(zappy_server_t *infos, ai_t *player)
{
    char *response = pnw(player);

    send_guis(infos, response, NULL);
    MY_FREE(response);
}
