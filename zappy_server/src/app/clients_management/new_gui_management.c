/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** new_gui_management
*/

#include "gui.h"
#include "protocol.h"
#include "zappy_server.h"

static void eggs_event(zappy_server_t *zappy_server, client_t *client)
{
    node_t *team_entry = NULL;
    tail_node_t *egg_entry = NULL;

    LIST_FOREACH(team_entry, &zappy_server->teams, entries)
    TAILQ_FOREACH(egg_entry, &TEAM(team_entry)->eggs, entries) {
        enw_event(client, EGG(egg_entry));
        if (EGG(egg_entry)->is_mature)
            eht_event(client, EGG(egg_entry));
    }
}

static void new_gui_events(zappy_server_t *zappy_server, client_t *client)
{
    node_t *entry = NULL;

    msz_event(zappy_server, client);
    sgt_event(zappy_server, client);
    mct_event(zappy_server, client);
    tna_event(zappy_server, client);
    LIST_FOREACH(entry, &zappy_server->players, entries) {
        pnw_event(AI(entry), client);
        pin_event(zappy_server, client, AI(entry)->player_id);
        plv_event(zappy_server, client, AI(entry)->player_id);
    }
    eggs_event(zappy_server, client);
}

void handle_new_gui_client(zappy_server_t *zappy_server, node_t *client)
{
    node_t *gui_node = NULL;
    zappy_client_t *new_gui = NULL;
    if (!(gui_node = malloc(sizeof(*gui_node)))) {
        enqueue_messages(
        &CLIENT(client)->communicator, WRITE, KO CRLF, NULL);
        ERROR("Gui memory allocation failed", );
    }
    if (!(new_gui = calloc(1, sizeof(*new_gui)))) {
        MY_FREE(new_gui);
        enqueue_messages(
        &CLIENT(client)->communicator, WRITE, KO CRLF, NULL);
        ERROR("Gui memory allocation failed", );
    }
    new_gui->type = GUI;
    new_gui->data.gui.client = client;
    gui_node->data = new_gui;
    CLIENT(client)->data = gui_node;
    CLIENT(client)->release_data = &gui_disconnection;
    LIST_INSERT_HEAD(&zappy_server->guis, gui_node, entries);
    new_gui_events(zappy_server, CLIENT(client));
}
