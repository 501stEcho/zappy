/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** protocol
*/

#pragma once

#include <sys/stat.h>
#include <sys/time.h>

#include "zappy_server.h"
#include "server.h"
#include "command.h"

#include "ai_messages.h"
#include "gui_messages.h"

#define CRLF "\n"

#define KO "ko"

#define GREETING "WELCOME"

#define GRAPHIC_CMD "GRAPHIC"

#define INCANTATION_START_MESSAGE "Elevation underway"

#define INCANTATION_END_MESSAGE "Current level:"

#define MAX_PORT USHRT_MAX
#define MIN_PORT 1024
#define HOST_PORT_LEN INET_ADDRSTRLEN + 7

typedef struct command_handler_s {
    const char *mnemonique;
    void (*handler)(zappy_server_t *zappy_server,
        client_t *client, command_t *command);
    uint8_t nb_args;
} command_handler_t;

// Input commands :

extern const command_handler_t input_commands[];

void clients_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command __attribute__((unused)));
void send_ais_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command);
void send_guis_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command);

void quit_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command __attribute__((unused)));

void map_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command __attribute__((unused)));

void clear_command(zappy_server_t *zappy_server __attribute__((unused)),
    client_t *client __attribute__((unused)),
    command_t *command __attribute__((unused)));

void pause_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command __attribute__((unused)));

void start_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command __attribute__((unused)));

void handle_input_command(zappy_server_t *zappy_server);

// Clients management :

void handle_client_type(zappy_server_t *zappy_server,
    node_t *client, char *command);

void send_clients(zappy_server_t *zappy_server, ...);

// AI management :

void ai_disconnection(void *ai_node);
void all_ai_disconnection(zappy_server_t *zappy_client);

void handle_new_ai_client(zappy_server_t *zappy_server,
    node_t *client, team_t *team);

void send_ai_connection_infos(zappy_server_t *zappy_server, team_t *team,
    node_t *ai_node, egg_t *egg);

extern const command_handler_t ai_commands[];
void send_ais(zappy_server_t *zappy_server, ...);
void enqueue_command(zappy_server_t *zappy_server,
    client_t *client, char *command);
void handle_ai_protocol(zappy_server_t *zappy_server,
    const struct timeval *now);

// GUI management :

void gui_disconnection(void *gui);

extern const command_handler_t gui_commands[];
void send_guis(zappy_server_t *zappy_server, ...);

void handle_new_gui_client(zappy_server_t *zappy_server, node_t *client);

// Zappy protocol :

void send_greeting(client_t *client);

void exec_zappy_protocol_final_checks(zappy_server_t *zappy_serve,
    const struct timeval *now);

void handle_command(zappy_server_t *zappy_server, client_t *client,
    char *buffer, const command_handler_t command_tab[]);
void handle_unkown_user_command(zappy_server_t *zappy_server,
    node_t *client, char *buffer);
void handle_user_command(zappy_server_t *zappy_server,
    client_t *client, char *buffer);

void exec_zappy_protocol(zappy_server_t *zappy_server,
    const struct timeval *now);
