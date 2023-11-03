/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** set
*/

#include "ai.h"
#include "gui.h"
#include "protocol.h"
#include "ai_messages.h"
#include "zappy_server.h"

static bool set_elem_fourth(
zappy_server_t *server, client_t *client, char *elem, const coord_t *coords)
{
    if (strcmp(elem, "thystame") == 0) {
        if (AI_CLIENT(client)->drone->inventory.thystame == 0)
            return false;
        server->map->tiles[coords->y][coords->x].thystame++;
        server->global_inventory->thystame++;
        AI_CLIENT(client)->drone->inventory.thystame--;
        pdr_all(server, AI_CLIENT(client)->player_id, THYSTAME);
        return true;
    }
    return false;
}

static bool set_elem_third(
zappy_server_t *server, client_t *client, char *elem, const coord_t *coords)
{
    if (strcmp(elem, "mendiane") == 0) {
        if (AI_CLIENT(client)->drone->inventory.mendiane == 0)
            return false;
        server->map->tiles[coords->y][coords->x].mendiane++;
        server->global_inventory->mendiane++;
        AI_CLIENT(client)->drone->inventory.mendiane--;
        pdr_all(server, AI_CLIENT(client)->player_id, MENDIANE);
        return true;
    }
    if (strcmp(elem, "phiras") == 0) {
        if (AI_CLIENT(client)->drone->inventory.phiras == 0)
            return false;
        server->map->tiles[coords->y][coords->x].phiras++;
        server->global_inventory->phiras++;
        AI_CLIENT(client)->drone->inventory.phiras--;
        pdr_all(server, AI_CLIENT(client)->player_id, PHIRAS);
        return true;
    }
    return set_elem_fourth(server, client, elem, coords);
}

static bool set_elem_bis(
zappy_server_t *server, client_t *client, char *elem, const coord_t *coords)
{
    if (strcmp(elem, "deraumere") == 0) {
        if (AI_CLIENT(client)->drone->inventory.deraumere == 0)
            return false;
        server->map->tiles[coords->y][coords->x].deraumere++;
        server->global_inventory->deraumere++;
        AI_CLIENT(client)->drone->inventory.deraumere--;
        pdr_all(server, AI_CLIENT(client)->player_id, DERAUMERE);
        return true;
    }
    if (strcmp(elem, "sibur") == 0) {
        if (AI_CLIENT(client)->drone->inventory.sibur == 0)
            return false;
        server->map->tiles[coords->y][coords->x].sibur++;
        server->global_inventory->sibur++;
        AI_CLIENT(client)->drone->inventory.sibur--;
        pdr_all(server, AI_CLIENT(client)->player_id, SIBUR);
        return true;
    }
    return set_elem_third(server, client, elem, coords);
}

static bool set_food(
zappy_server_t *server, client_t *client, char *elem, const coord_t *coords)
{
    if (strcmp(elem, "food") == 0) {
        if (AI_CLIENT(client)->drone->inventory.food == 0)
            return false;
        server->map->tiles[coords->y][coords->x].food++;
        server->global_inventory->food++;
        AI_CLIENT(client)->drone->inventory.food--;
        pdr_all(server, AI_CLIENT(client)->player_id, FOOD);
        return true;
    }
    if (strcmp(elem, "linemate") == 0) {
        if (AI_CLIENT(client)->drone->inventory.linemate == 0)
            return false;
        server->map->tiles[coords->y][coords->x].linemate++;
        server->global_inventory->linemate++;
        AI_CLIENT(client)->drone->inventory.linemate--;
        pdr_all(server, AI_CLIENT(client)->player_id, LINEMATE);
        return true;
    }
    return set_elem_bis(server, client, elem, coords);
}

void set_cmd(zappy_server_t *server, client_t *client, command_t *cmd)
{
    coord_t coords = {.x = AI_CLIENT(client)->drone->coords.x,
        .y = AI_CLIENT(client)->drone->coords.y};

    if (!set_food(server, client, cmd->segments[1], &coords))
        return enqueue_messages(&client->communicator,
            WRITE, AI_KO CRLF, NULL);
    enqueue_messages(&client->communicator, WRITE,
        AI_OK CRLF, NULL);
    pin_all(server, AI_CLIENT(client)->player_id);
    bct_all(server, AI_CLIENT(client)->drone->coords.x,
        AI_CLIENT(client)->drone->coords.y);
}
