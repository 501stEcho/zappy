/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** ai_protocol
*/

#include "zappy_server.h"
#include "protocol.h"
#include "gui.h"
#include "ai.h"

const command_handler_t ai_commands[] = {
    {.mnemonique = AI_Forward, .handler = &forward_cmd, .nb_args = 0},
    {.mnemonique = AI_Right, .handler = &right_cmd, .nb_args = 0},
    {.mnemonique = AI_Left, .handler = &left_cmd, .nb_args = 0},
    {.mnemonique = AI_Look, .handler = &look_cmd, .nb_args = 0},
    {.mnemonique = AI_Inventory, .handler = &inventory_cmd, .nb_args = 0},
    {.mnemonique = AI_Broadcast, .handler = &broadcast_cmd, .nb_args = 1},
    {.mnemonique = AI_Connect_nbr, .handler = &connect_nbr_cmd, .nb_args = 0},
    {.mnemonique = AI_Fork, .handler = &fork_cmd, .nb_args = 0},
    {.mnemonique = AI_Eject, .handler = &eject_cmd, .nb_args = 0},
    {.mnemonique = AI_Take, .handler = &take_cmd, .nb_args = 1},
    {.mnemonique = AI_Set, .handler = &set_cmd, .nb_args = 1},
    {.mnemonique = AI_Incantation, .handler = &incantation_cmd, .nb_args = 0},
    {}
};

void send_ais(zappy_server_t *zappy_server, ...)
{
    node_t *entry = NULL;
    va_list args;
    va_list tmp;

    va_start(args, zappy_server);
    LIST_FOREACH(entry, &zappy_server->players, entries) {
        va_copy(tmp, args);
        if (AI(entry)->client && AI(entry)->alive)
            v_enqueue_messages(&CLIENT(AI(entry)->client)->communicator,
                WRITE, tmp);
    }
    va_end(args);
}

static void handle_dead_ai(zappy_server_t *zappy_server, node_t *ai_client)
{
    if (zappy_server->state == END) {
        if (AI(ai_client)->client && (is_communication_empty(
            &CLIENT(AI(ai_client)->client)->communicator, WRITE))) {
            LIST_REMOVE(AI(ai_client)->client, entries);
            close_client(AI(ai_client)->client);
        }
        return;
    }
    if (!AI(ai_client)->client) {
        pdi_all(zappy_server, AI(ai_client)->player_id);
        remove_from_incantations(zappy_server, AI(ai_client));
        free_ai(ai_client);
        return;
    }
    if (is_communication_empty(&CLIENT(AI(ai_client)->client)->communicator,
        WRITE)) {
        remove_from_incantations(zappy_server, AI(ai_client));
        free_ai(ai_client);
        return;
    }
}

void handle_ai_protocol(zappy_server_t *zappy_server,
    const struct timeval *now)
{
    node_t *current = NULL;
    node_t *entry = NULL;

    entry = LIST_FIRST(&zappy_server->players);
    while (entry) {
        current = entry;
        entry = LIST_NEXT(entry, entries);
        if (!AI(current)->alive) {
            handle_dead_ai(zappy_server, current);
            continue;
        }
        if (zappy_server->state != RUNNING)
            continue;
        if (!AI(current)->incantating)
            handle_ai_command(zappy_server, CLIENT(AI(current)->client), now);
        handle_ai_food(zappy_server, CLIENT(AI(current)->client), now);
    }
}
