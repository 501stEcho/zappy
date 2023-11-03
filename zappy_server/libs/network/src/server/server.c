/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** server
*/
#include "server.h"

bool close_server(server_t *server)
{
    printf("Server shutting down.\n");
    close_clients(server);
    if (close(server->communicator.socket) < 0)
        PERROR("Server closure : close failed.", false);
    return true;
}

bool init_server(server_t *server)
{
    struct sockaddr_in addr = {.sin_family = AF_INET,
        .sin_port = htons(server->port),.sin_addr = {.s_addr = INADDR_ANY}};
    int optval = 1;

    if ((server->communicator.socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        PERROR("Server socket creation failed.", false);
    if ((setsockopt(server->communicator.socket, SOL_SOCKET,
        SO_REUSEADDR, &optval, sizeof(int)) < 0) ||
        (bind(server->communicator.socket,
        (struct sockaddr *)&addr, sizeof(addr)) < 0)) {
        if (close(server->communicator.socket) < 0)
            PERROR("Bind failed : close failed.", false);
        PERROR("Bind failed.", false);
    }
    if (listen(server->communicator.socket, 128) < 0) {
        if (close(server->communicator.socket) < 0)
            PERROR("Listen failed : close failed.", false);
        PERROR("Listen failed.", false);
    }
    return true;
}
