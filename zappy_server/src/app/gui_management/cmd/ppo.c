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

static char *ppo(zappy_server_t *infos, unsigned int id)
{
    char *response = NULL;
    node_t *entry = NULL;

    LIST_FOREACH(entry, &infos->players, entries)
        if (AI(entry)->player_id == id) {
            asprintf(&response, GUI_PLAYER_POSITION " %d %d %d %d" CRLF, id,
                AI(entry)->drone->coords.x, AI(entry)->drone->coords.y,
                AI(entry)->drone->direction);
            return response;
        }
    return NULL;
}

bool ppo_event(zappy_server_t *infos, client_t *client, unsigned int id)
{
    char *response = ppo(infos, id);

    if (response) {
        enqueue_messages(&CLIENT(client)->communicator, WRITE, response, NULL);
        MY_FREE(response);
        return true;
    }
    return false;
}

void ppo_all(zappy_server_t *infos, unsigned int id)
{
    char *response = ppo(infos, id);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}

void ppo_cmd(zappy_server_t *infos, client_t *client, command_t *cmd)
{
    unsigned int id = 0;

    id = atoi(cmd->segments[1]);
    if (!ppo_event(infos, client, id))
        sbp_event(client);
}
