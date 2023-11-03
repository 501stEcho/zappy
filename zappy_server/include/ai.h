/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ai_cmd
*/

#pragma once

#include <stdint.h>

#include "zappy_server.h"
#include "protocol.h"
#include "my_time.h"
#include "command.h"
#include "vector.h"

#define START_FOOD 9

#define START_FOOD_TIME 126

#define AI_COMMAND(node) ((ai_command_t *)node->data)

#define SMALL_ANGLE atan(0.5 / 1.5) * 2.0

#define HALF_SMALL_ANGLE SMALL_ANGLE / 2.0

#define BIG_ANGLE atan((sqrt(2.0) / 2.0) / sqrt(2.0)) * 2.0

#define RADIAN_CIRCLE 2.0 * M_PI

typedef struct command_execution_time_s {
    const command_handler_t *command;
    bool (*beging_handler)(zappy_server_t *zappy_server,
        client_t *client, command_t *command);
    uint8_t time_limit;
} command_execution_time_t;

typedef struct ai_command_s {
    struct timeval duration;
    const command_handler_t *command_handler;
    char *buffer;
    bool (*beging_handler)(zappy_server_t *zappy_server,
        client_t *client, command_t *command);
} ai_command_t;

void handle_ai_food(zappy_server_t *zappy_server, client_t *client,
    const struct timeval *now);

bool exec_command_begin(zappy_server_t *zappy_server,
    client_t *client, ai_command_t *ai_command);
void handle_next_command_begin(zappy_server_t *zappy_server, client_t *client);

void free_ai_command(ai_command_t *ai_command);
ai_command_t *get_ai_command(zappy_server_t *zappy_server, char *buffer);
void enqueue_command(zappy_server_t *zappy_server,
    client_t *client, char *buffer);
void handle_ai_command(zappy_server_t *zappy_server, client_t *client,
    const struct timeval *now);

void forward_cmd(zappy_server_t *server, client_t *client, command_t *cmd);

void right_cmd(zappy_server_t *server __attribute__((unused)),
    client_t *client, command_t *cmd __attribute__((unused)));

void left_cmd(zappy_server_t *server __attribute__((unused)),
    client_t *client, command_t *cmd __attribute__((unused)));

int get_nb_players(int x, int y, zappy_server_t *server);
int get_nb_eggs(int x, int y, zappy_server_t *server);

char *append_str(char *str, char *to_append, unsigned int space);

char *get_look_response_north(zappy_server_t *server, coord_t coord, int level);
char *get_look_response_west(zappy_server_t *server, coord_t coord, int level);
char *get_look_response_south(zappy_server_t *server, coord_t coord, int level);
char *get_look_response_east(zappy_server_t *server, coord_t coord, int level);

char *get_tile_inventory(inventory_t *tile, int x, int y,
    zappy_server_t *server);
void look_cmd(zappy_server_t *server, client_t *client,
    command_t *cmd __attribute__((unused)));

void inventory_cmd(zappy_server_t *server __attribute__((unused)),
    client_t *client, command_t *cmd __attribute__((unused)));

void get_coords_possibilities(zappy_server_t *zappy_server,
    const drone_t *drone, coord_t (*possibilities)[8]);
vectot_t get_direction_vector(direction_t direction);
int get_message_receive_direction(double angle);

void broadcast_cmd(zappy_server_t *zappy_server,
    client_t *client, command_t *command);

char *parse_response(char *str);

void connect_nbr_cmd(zappy_server_t *zappy_server __attribute__((unused)),
    client_t *client, command_t *command __attribute__((unused)));

bool fork_begin(zappy_server_t *zappy_server,
    client_t *client, command_t *command);
void fork_cmd(zappy_server_t *zappy_server,
    client_t *client, command_t *command __attribute__((unused)));

bool eject_eggs(zappy_server_t *zappy_server, client_t *client);
bool eject_players(zappy_server_t *server, client_t *client);
void eject_cmd(zappy_server_t *server, client_t *client,
    command_t *cmd __attribute__((unused)));

void take_cmd(zappy_server_t *server, client_t *client, command_t *cmd);

void set_cmd(zappy_server_t *server, client_t *client, command_t *cmd);

void incantation_cmd(zappy_server_t *zappy_server,
    client_t *client, command_t *command __attribute__((unused)));
