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

void tna_event(zappy_server_t *infos, client_t *client)
{
    node_t *entry = NULL;
    char *response = NULL;

    LIST_FOREACH(entry, &infos->teams, entries) {
        asprintf(&response, GUI_TEAM_NAME " %s" CRLF, TEAM(entry)->name);
        enqueue_messages(&client->communicator, WRITE, response, NULL);
        MY_FREE(response);
    }
}

void tna_cmd(zappy_server_t *infos, client_t *client,
    command_t *cmd __attribute__((unused)))
{
    tna_event(infos, client);
}
