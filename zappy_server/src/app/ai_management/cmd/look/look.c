/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** look
*/

#include "ai.h"
#include "protocol.h"
#include "zappy_server.h"

char *append_str(char *str, char *to_append, unsigned int space)
{
    char *new_str = NULL;

    if (str == NULL)
        return strdup(to_append);
    new_str = calloc((strlen(str) + strlen(to_append) + 1) +
        (space ? 1 : 0), sizeof(char));
    if (new_str == NULL)
        return NULL;
    strcpy(new_str, str);
    if (space)
        strcat(new_str, "|");
    strcat(new_str, to_append);
    free(str);
    return new_str;
}

char *get_tile_inventory(inventory_t *tile, int x, int y,
    zappy_server_t *server)
{
    char *response = NULL;
    unsigned int one = 0;
    int nb_players = get_nb_players(x, y, server);
    int nb_eggs = server->display_eggs ? get_nb_eggs(x, y, server) : 0;
    char *items[] = {"player", "food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame", "egg"};
    int quantities[] = {nb_players, tile->food, tile->linemate, tile->deraumere,
        tile->sibur, tile->mendiane, tile->phiras, tile->thystame, nb_eggs};
    int num_items = sizeof(items) / sizeof(items[0]);

    for (int i = 0; i < num_items; i++)
        for (int j = 0; j < quantities[i]; j++)
            response = append_str(response, items[i], one++);
    return append_str(response, ",", 0);
}

static char *get_look_response(zappy_server_t *server, coord_t coord,
    direction_t direction, int level)
{
    char *response = NULL;

    switch (direction) {
    case NORTH:
        response = get_look_response_north(server, coord, level);
        break;
    case EAST: response = get_look_response_east(server, coord, level); break;
    case SOUTH:
        response = get_look_response_south(server, coord, level);
        break;
    case WEST: response = get_look_response_west(server, coord, level); break;
    }
    response = parse_response(response);
    return response;
}

void look_cmd(zappy_server_t *server, client_t *client,
    command_t *cmd __attribute__((unused)))
{
    char *response = NULL;
    node_t *tmp_cli = NULL;
    direction_t direction = -1;

    LIST_FOREACH(tmp_cli, &server->players, entries)
        if (AI(tmp_cli)->player_id == AI_CLIENT(client)->player_id) {
            direction = AI(tmp_cli)->drone->direction;
            break;
        }
    response = get_look_response(server, AI_CLIENT(client)->drone->coords,
    direction, AI_CLIENT(client)->drone->level);
    enqueue_messages(&client->communicator, WRITE,
        response, CRLF, NULL);
    free(response);
}
