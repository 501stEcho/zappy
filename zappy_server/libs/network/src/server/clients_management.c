/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** clients_management
*/

#include "server.h"

static void free_buffer(tail_node_t *buffer_node)
{
    if (buffer_node->data)
        MY_FREE(buffer_node->data);
    MY_FREE(buffer_node);
}

void close_client(node_t *client)
{
    printf("/===========Closing client===========\\\n");
    if (CLIENT(client)->data && CLIENT(client)->release_data)
        CLIENT(client)->release_data(CLIENT(client)->data);
    close(CLIENT(client)->communicator.socket);
    free_tail(&CLIENT(client)->communicator.read, &free_buffer);
    free_tail(&CLIENT(client)->communicator.write, &free_buffer);
    MY_FREE(client->data);
    MY_FREE(client);
    printf("\\====================================/\n");
}

void close_clients(server_t *server)
{
    free_list(&server->clients, &close_client);
}

static node_t *create_new_client(void)
{
    node_t *client_node = NULL;
    client_t *new_client = NULL;
    if (!(client_node = malloc(sizeof(*client_node))))
        PERROR("Client memory allocation failed", NULL);
    if (!(new_client = malloc(sizeof(*new_client)))) {
        MY_FREE(client_node);
        PERROR("Client memory allocation failed", NULL);
    }
    new_client->communicator.socket = -1;
    TAILQ_INIT(&new_client->communicator.read);
    TAILQ_INIT(&new_client->communicator.write);
    new_client->data = NULL;
    new_client->release_data = NULL;
    client_node->data = new_client;
    return client_node;
}

void handle_new_connection(server_t *server)
{
    socklen_t client_len = sizeof(struct sockaddr_in);
    node_t *client_node = NULL;

    if (!(client_node = create_new_client()))
        PERROR("Client memory allocation failed", );
    CLIENT(client_node)->communicator.socket =
    accept(server->communicator.socket,
    (struct sockaddr *)&CLIENT(client_node)->addr, &client_len);
    if (CLIENT(client_node)->communicator.socket < 0) {
        MY_FREE(client_node->data);
        MY_FREE(client_node);
        PERROR("Accept failed.", );
    }
    LIST_INSERT_HEAD(&server->clients, client_node, entries);
    if (server->connection_handler)
        server->connection_handler(CLIENT(client_node));
    display_client_connection(CLIENT(client_node));
}
