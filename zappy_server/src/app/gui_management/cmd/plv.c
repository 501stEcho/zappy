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

static char *plv(zappy_server_t *infos, unsigned int id)
{
    char *response = NULL;
    node_t *entry = NULL;

    LIST_FOREACH(entry, &infos->players, entries) {
        if (AI(entry)->player_id == id) {
            asprintf(&response, GUI_PLAYER_LEVEL " %d %d" CRLF,
                id, AI(entry)->drone->level);
            return response;
        }
    }
    return NULL;
}

bool plv_event(zappy_server_t *infos, client_t *client, unsigned int id)
{
    char *response = plv(infos, id);

    if (response) {
        enqueue_messages(&client->communicator, WRITE, response, NULL);
        MY_FREE(response);
        return true;
    }
    return false;
}

void plv_all(zappy_server_t *infos, unsigned int id)
{
    char *response = plv(infos, id);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}

void plv_cmd(zappy_server_t *infos, client_t *client, command_t *cmd)
{
    int id = 0;

    id = atoi(cmd->segments[1]);
    if (!plv_event(infos, client, id))
        sbp_event(client);
}
