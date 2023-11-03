/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** select_management
*/

#include "server.h"

int handle_select(server_t *server, int high_socket, struct timeval *timeout)
{
    switch (select(high_socket + 1, &server->read_fds, &server->write_fds,
    &server->except_fds, timeout)) {
    case -1:
        if (errno == EINTR)
            return 0;
        PERROR("Select failed.", -1);
    default:
        if (!handle_fdsets(server))
            ERROR("Major error detected.", -1);
        return 1;
    }
    return 1;
}
