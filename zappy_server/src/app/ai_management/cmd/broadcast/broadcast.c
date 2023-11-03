/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** broadcast
*/

#include "zappy_server.h"
#include "ai_messages.h"
#include "protocol.h"
#include "gui.h"
#include "ai.h"

static void send_shortest_way(const coord_t *sender_coords, ai_t *receiver,
    const char *message)
{
    vectot_t direction_vect =
    get_direction_vector(receiver->drone->direction);
    vectot_t broadcast_vect = new_vector(receiver->drone->coords.x,
    receiver->drone->coords.y, sender_coords->x, sender_coords->y);
    double angle1 = atan2(broadcast_vect.y, broadcast_vect.x);
    double angle2 = atan2(direction_vect.y, direction_vect.x);
    double angle =
    (angle1 - angle2) < 0 ? 2.0 * M_PI + (angle1 - angle2) : (angle1 - angle2);
    int direction = get_message_receive_direction(angle);
    char *response = NULL;

    asprintf(&response, AI_BROADCAST_MESSAGE " %d, %s" CRLF,
        direction, message);
    enqueue_messages(&CLIENT(receiver->client)->communicator, WRITE,
        response, NULL);
    MY_FREE(response);
}

static void send_message(zappy_server_t *zappy_server, const ai_t *sender,
    ai_t *receiver, const char *message)
{
    coord_t pos[8];
    coord_t closest = sender->drone->coords;
    double close_d = euclidian_distance(receiver->drone->coords.x,
    receiver->drone->coords.y, sender->drone->coords.x,
    sender->drone->coords.y);
    double distance;

    get_coords_possibilities(zappy_server, sender->drone, &pos);
    for (uint8_t i = 0; i < 8; ++i)
        if ((distance = euclidian_distance(receiver->drone->coords.x,
            receiver->drone->coords.y, pos[i].x, pos[i].y)) < close_d) {
            close_d = distance;
            closest = pos[i];
        }
    send_shortest_way(&closest, receiver, message);
}

static void handle_broadcast(zappy_server_t *zappy_server,
    const ai_t *sender, const char *message)
{
    node_t *entry = NULL;
    char *response = NULL;

    asprintf(&response, AI_BROADCAST_MESSAGE " %d, %s" CRLF, 0, message);
    LIST_FOREACH(entry, &zappy_server->players, entries) {
        if ((AI(entry)->player_id == sender->player_id) ||
            !AI(entry)->alive || !AI(entry)->client)
            continue;
        if ((AI(entry)->drone->coords.x == sender->drone->coords.x) &&
            (AI(entry)->drone->coords.y == sender->drone->coords.y)) {
            enqueue_messages(
            &CLIENT(AI(entry)->client)->communicator, WRITE, response, NULL);
            continue;
        }
        send_message(zappy_server, sender, AI(entry), message);
    }
    MY_FREE(response);
}

void broadcast_cmd(zappy_server_t *zappy_server,
    client_t *client, command_t *command)
{
    handle_broadcast(zappy_server, AI_CLIENT(client), command->segments[1]);
    enqueue_messages(&client->communicator, WRITE, AI_OK, CRLF, NULL);
    pbc_all(zappy_server, AI_CLIENT(client)->player_id, command->segments[1]);
}
