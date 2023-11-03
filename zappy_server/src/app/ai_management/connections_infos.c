/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** connections_infos
*/

#include "zappy_server.h"
#include "protocol.h"
#include "gui.h"

void send_ai_connection_infos(zappy_server_t *zappy_server, team_t *team,
    node_t *ai_node, egg_t *egg)
{
    char clients_nb[CLIENTSNB_STR_MAX_SIZE + 1] = {};
    char coords[DIM_STR_MAX_SIZE + 1] = {};

    snprintf(clients_nb, CLIENTSNB_STR_MAX_SIZE + 1, "%hu",
        team->nb_matures_eggs);
    snprintf(coords, DIM_STR_MAX_SIZE + 1, "%hu %hu",
        zappy_server->width, zappy_server->height);
    enqueue_messages(&CLIENT(AI(ai_node)->client)->communicator, WRITE,
        clients_nb, CRLF, coords, CRLF, NULL);
    pnw_all(zappy_server, AI(ai_node));
    pin_all(zappy_server, AI(ai_node)->player_id);
    ebo_all(zappy_server, egg->egg_id);
}
