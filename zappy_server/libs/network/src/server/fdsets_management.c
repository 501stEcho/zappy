/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** fdsets_management
*/

#include "server.h"

static bool check_fdexcept(server_t *server)
{
    node_t *tmp = NULL;
    node_t *to_close = NULL;

    if (FD_ISSET(STDIN_FILENO, &server->except_fds))
        return false;
    if (FD_ISSET(server->communicator.socket, &server->except_fds))
        return false;
    tmp = LIST_FIRST(&server->clients);
    while (tmp) {
        if (FD_ISSET(CLIENT(tmp)->communicator.socket, &server->except_fds)) {
            to_close = tmp;
            tmp = LIST_NEXT(tmp, entries);
            LIST_REMOVE(to_close, entries);
            close_client(to_close);
            continue;
        }
        tmp = LIST_NEXT(tmp, entries);
    }
    return true;
}

static void read_from_stdin(server_t *server)
{
    char buff[BUFFLEN + 1] = {};
    ssize_t bytes;

    bytes = read(STDIN_FILENO, &buff, BUFFLEN);
    if (bytes <= 0)
        PERROR("Failed to read from stdin", );
    enqueue_message(&server->communicator, READ, buff, bytes);
}

static void check_fdread(server_t *server)
{
    node_t *tmp = NULL;
    node_t *to_close = NULL;

    if (FD_ISSET(STDIN_FILENO, &server->read_fds))
        read_from_stdin(server);
    if (FD_ISSET(server->communicator.socket, &server->read_fds))
        handle_new_connection(server);
    tmp = LIST_FIRST(&server->clients);
    while (tmp) {
        if (FD_ISSET(CLIENT(tmp)->communicator.socket, &server->read_fds) &&
        (!read_from_peer(&CLIENT(tmp)->communicator))) {
            to_close = tmp;
            tmp = LIST_NEXT(tmp, entries);
            LIST_REMOVE(to_close, entries);
            close_client(to_close);
            continue;
        }
        tmp = LIST_NEXT(tmp, entries);
    }
}

static void check_fdwrite(server_t *server)
{
    node_t *tmp = NULL;
    tail_node_t *to_write = NULL;

    tmp = LIST_FIRST(&server->clients);
    while (tmp) {
        if (FD_ISSET(CLIENT(tmp)->communicator.socket, &server->write_fds) &&
            (to_write = TAILQ_FIRST(&CLIENT(tmp)->communicator.write)))
            write_to_peer(&CLIENT(tmp)->communicator);
        tmp = LIST_NEXT(tmp, entries);
    }
}

bool handle_fdsets(server_t *server)
{
    if (!check_fdexcept(server))
        ERROR("Exception detected.", false);
    check_fdread(server);
    check_fdwrite(server);
    return true;
}
