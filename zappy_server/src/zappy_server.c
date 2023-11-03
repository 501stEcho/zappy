/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** server
*/

#include "zappy_server.h"
#include "protocol.h"
#include "server.h"

static void free_buffer(tail_node_t *buffer_node)
{
    if (buffer_node->data)
        MY_FREE(buffer_node->data);
    MY_FREE(buffer_node);
}

bool close_zappy_server(zappy_server_t *zappy_server)
{
    bool status = close_server(&zappy_server->server);

    free_incantations(zappy_server);
    free_ais(&zappy_server->players);
    free_teams(&zappy_server->teams);
    free_guis(&zappy_server->guis);
    free(zappy_server->global_inventory);
    free_map(zappy_server->map);
    free_tail(&zappy_server->server.communicator.read, &free_buffer);
    free_tail(&zappy_server->server.communicator.write, &free_buffer);
    return status;
}

bool init_zappy_server(zappy_server_t *zappy_server)
{
    if (!init_server(&zappy_server->server))
        ERROR("Server init failed", false);
    if (zappy_server->state == RUNNING)
        zappy_server->server.connection_handler = &send_greeting;
    FD_ZERO(&zappy_server->server.read_fds);
    FD_ZERO(&zappy_server->server.write_fds);
    FD_ZERO(&zappy_server->server.except_fds);
    zappy_server->server.running = true;
    LIST_INIT(&zappy_server->server.clients);
    TAILQ_INIT(&zappy_server->server.communicator.read);
    TAILQ_INIT(&zappy_server->server.communicator.write);
    calculate_duration(&zappy_server->refill_duration, REFILL_TIME,
        zappy_server->freq);
    LIST_INIT(&zappy_server->server.clients);
    LIST_INIT(&zappy_server->players);
    LIST_INIT(&zappy_server->guis);
    LIST_INIT(&zappy_server->incantations);
    return true;
}

bool zappy_server_management(zappy_server_t *zappy_server)
{
    int high_socket = zappy_server->server.communicator.socket;
    struct timeval now = {};

    gettimeofday(&zappy_server->refill_timer, NULL);
    while (*is_running() && zappy_server->server.running) {
        reset_fs_sets(&zappy_server->server);
        high_socket = get_high_socket(&zappy_server->server);
        switch (handle_select(&zappy_server->server,high_socket,
            zappy_server->time_out_needed ? &zappy_server->timeout : NULL)) {
            case -1: PERROR("Select failed.", false);
            case 0: return true;
            default: break;
        }
        gettimeofday(&now, NULL);
        zappy_server->time_out_needed = false;
        exec_zappy_protocol(zappy_server, &now);
    }
    return true;
}
