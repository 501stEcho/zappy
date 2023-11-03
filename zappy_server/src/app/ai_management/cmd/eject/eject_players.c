/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** eject_players
*/

#include "zappy_server.h"
#include "protocol.h"
#include "gui.h"
#include "ai.h"

static uint8_t relative_eject_direction(direction_t ejector_direction,
    direction_t bollosed_direction)
{
    if (ejector_direction == bollosed_direction)
        return 5;
    if (abs((int8_t)bollosed_direction - (int8_t)ejector_direction) == 2)
        return 1;
    if ((ejector_direction - bollosed_direction == 1) ||
        ((bollosed_direction == WEST) && (ejector_direction == NORTH)))
        return 3;
    if ((bollosed_direction - ejector_direction == 1) ||
        ((bollosed_direction == NORTH) && (ejector_direction == WEST)))
        return 7;
    return 0;
}

static void print_ejection(node_t *client, direction_t ejector_direction,
    direction_t bollosed_direction)
{
    uint8_t relative_direction = relative_eject_direction(ejector_direction,
        bollosed_direction);
    char *response = NULL;

    asprintf(&response, "eject: %d\n", relative_direction);
    enqueue_messages(&CLIENT(client)->communicator, WRITE, response, NULL);
    MY_FREE(response);
}

static void eject_a_player(zappy_server_t *server, ai_t *ref, ai_t *tmp_cli)
{
    uint8_t x = ref->drone->coords.x;
    uint8_t y = ref->drone->coords.y;

    if (ref->drone->direction == NORTH)
        tmp_cli->drone->coords.y = (y + 1 >= server->map->height) ? 0 : y + 1;
    if (ref->drone->direction == EAST)
        tmp_cli->drone->coords.x = (x + 1 >= server->map->width) ? 0 : x + 1;
    if (ref->drone->direction == SOUTH)
        tmp_cli->drone->coords.y =
            (y - 1 < 0) ? server->map->height - 1 : y - 1;
    if (ref->drone->direction == WEST)
        tmp_cli->drone->coords.x = (x - 1 < 0) ? server->map->width - 1 : x - 1;
    print_ejection(tmp_cli->client, ref->drone->direction,
        tmp_cli->drone->direction);
}

bool eject_players(zappy_server_t *server, client_t *client)
{
    node_t *tmp_cli = NULL;
    uint8_t x = AI_CLIENT(client)->drone->coords.x;
    uint8_t y = AI_CLIENT(client)->drone->coords.y;
    size_t id = AI_CLIENT(client)->player_id;
    bool status = false;

    LIST_FOREACH(tmp_cli, &server->players, entries) {
        if (!AI(tmp_cli)->alive ||
            AI(tmp_cli)->drone->coords.x != x ||
            AI(tmp_cli)->drone->coords.y != y ||
            AI(tmp_cli)->player_id == id)
            continue;
        status = true;
        eject_a_player(server, AI_CLIENT(client), AI(tmp_cli));
        ppo_all(server, AI(tmp_cli)->player_id);
    }
    return status;
}
