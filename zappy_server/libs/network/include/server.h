/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** server
*/

#pragma once

#include <linux/limits.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <uuid/uuid.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>

#include "my.h"
#include "linked_list.h"
#include "circular_buffer.h"
#include "comminucation.h"

#define MIN_PORT 1024
#define MAX_PORT USHRT_MAX

#define CLIENT(node) ((client_t *)node->data)

typedef struct client_s {
    struct sockaddr_in addr;
    communicator_t communicator;
    void *data;
    void (*release_data)(void *data);
} client_t;

typedef struct server_s {
    struct {
        fd_set read_fds;
        fd_set write_fds;
        fd_set except_fds;
    };
    bool running;
    uint16_t port;
    head_t clients;
    communicator_t communicator;
    void (*connection_handler)(client_t *new_client);
} server_t;

void display_client_connection(client_t *client);

void signal_handler(int sig);
bool *is_running(void);

bool close_server(server_t *server);
bool init_server(server_t *server);

int get_high_socket(server_t *server);
void reset_fs_sets(server_t *server);

void close_client(node_t *client);
void close_clients(server_t *server);
void handle_new_connection(server_t *server);

bool handle_fdsets(server_t *server);

int handle_select(server_t *server, int high_socket, struct timeval *timeout);
