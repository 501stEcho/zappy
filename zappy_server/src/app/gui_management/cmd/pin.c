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

static char *pin(zappy_server_t *infos, unsigned int id)
{
    char *response = NULL;
    node_t *entry = NULL;

    LIST_FOREACH(entry, &infos->players, entries)
        if (AI(entry)->player_id == id) {
            asprintf(&response,
                GUI_PLAYER_INVENTORY " %d %d %d %d %d %d %d %d %d %d" CRLF, id,
                AI(entry)->drone->coords.x,
                AI(entry)->drone->coords.y,
                AI(entry)->drone->inventory.food,
                AI(entry)->drone->inventory.linemate,
                AI(entry)->drone->inventory.deraumere,
                AI(entry)->drone->inventory.sibur,
                AI(entry)->drone->inventory.mendiane,
                AI(entry)->drone->inventory.phiras,
                AI(entry)->drone->inventory.thystame);
            return response;
        }
    return NULL;
}

bool pin_event(zappy_server_t *infos, client_t *client, unsigned int id)
{
    char *response = pin(infos, id);

    if (response) {
        enqueue_messages(&client->communicator, WRITE, response, NULL);
        MY_FREE(response);
        return true;
    }
    return false;
}

void pin_all(zappy_server_t *infos, unsigned int id)
{
    char *response = pin(infos, id);

    if (response)
        send_guis(infos, response, NULL);
    MY_FREE(response);
}

void pin_cmd(zappy_server_t *infos, client_t *client, command_t *cmd)
{
    int id = 0;

    id = atoi(cmd->segments[1]);
    if (!pin_event(infos, client, id))
        sbp_event(client);
}
