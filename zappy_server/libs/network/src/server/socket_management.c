/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** socket_management
*/

#include "server.h"

int get_high_socket(server_t *server)
{
    int high_socket = server->communicator.socket;
    node_t *tmp = NULL;

    LIST_FOREACH(tmp, &server->clients, entries)
    if (CLIENT(tmp)->communicator.socket > high_socket)
        high_socket = CLIENT(tmp)->communicator.socket;
    return high_socket;
}

void reset_fs_sets(server_t *server)
{
    node_t *tmp = NULL;

    FD_ZERO(&server->read_fds);
    FD_SET(STDIN_FILENO, &server->read_fds);
    FD_SET(server->communicator.socket, &server->read_fds);
    LIST_FOREACH(tmp, &server->clients, entries)
        FD_SET(CLIENT(tmp)->communicator.socket, &server->read_fds);
    FD_ZERO(&server->write_fds);
    LIST_FOREACH(tmp, &server->clients, entries)
        if (!TAILQ_EMPTY(&CLIENT(tmp)->communicator.write) &&
            !is_empty(BUFFER(TAILQ_FIRST(&CLIENT(tmp)->communicator.write))))
            FD_SET(CLIENT(tmp)->communicator.socket, &server->write_fds);
    FD_ZERO(&server->except_fds);
    FD_SET(STDIN_FILENO, &server->except_fds);
    FD_SET(server->communicator.socket, &server->except_fds);
    LIST_FOREACH(tmp, &server->clients, entries)
        FD_SET(CLIENT(tmp)->communicator.socket, &server->except_fds);
}
