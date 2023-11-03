/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** gui_protocol
*/

#include "zappy_server.h"
#include "gui_messages.h"
#include "protocol.h"
#include "gui.h"

const command_handler_t gui_commands[] = {
    {.mnemonique = GUI_MAP_SIZE, .handler = &msz_cmd, .nb_args = 0},
    {.mnemonique = GUI_TILE_CONTENT, .handler = &bct_cmd, .nb_args = 2},
    {.mnemonique = GUI_MAP_CONTENT, .handler = &mct_cmd, .nb_args = 0},
    {.mnemonique = GUI_TEAM_NAME, .handler = &tna_cmd, .nb_args = 0},
    {.mnemonique = GUI_PLAYER_POSITION, .handler = &ppo_cmd, .nb_args = 1},
    {.mnemonique = GUI_PLAYER_LEVEL, .handler = &plv_cmd, .nb_args = 1},
    {.mnemonique = GUI_PLAYER_INVENTORY, .handler = &pin_cmd, .nb_args = 1},
    {.mnemonique = GUI_GET_FREQUENCE, .handler = &sgt_cmd, .nb_args = 0},
    {.mnemonique = GUI_SET_FREQUENCE, .handler = &sst_cmd, .nb_args = 1},
    {}
};

void send_guis(zappy_server_t *zappy_server, ...)
{
    node_t *entry = NULL;
    va_list args;
    va_list tmp;

    va_start(args, zappy_server);
    LIST_FOREACH(entry, &zappy_server->guis, entries) {
        va_copy(tmp, args);
        v_enqueue_messages(&CLIENT(GUI(entry)->client)->communicator,
            WRITE, tmp);
    }
    va_end(args);
}
