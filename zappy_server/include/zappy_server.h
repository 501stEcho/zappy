/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** zappy_server
*/

#pragma once

#define _GNU_SOURCE

#include <stdint.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>

#include "linked_list.h"
#include "my_time.h"
#include "server.h"

#define DEFAULT_STATE RUNNING

#define MIN_X 10
#define MAX_X 30

#define MIN_Y 10
#define MAX_Y 30

#define DIM_STR_MAX_SIZE 5

#define MIN_CLIENTSNB 1
#define MAX_CLIENTSNB 200

#define CLIENTSNB_STR_MAX_SIZE 3

#define MIN_FREQ 2
#define MAX_FREQ 10000
#define DEFAULT_FREQ 100

#define COMMAND_LIMIT 10

#define STRART_LEVEL 1
#define MAX_LEVEL 8

#define MAX_LEVEL_WIN 6

#define REFILL_TIME 20

#define INCUBATION_TIME 600

#define INCANTATION_TIME 300

#define ZAPPY_CLIENT(client) \
    ((zappy_client_t *)((node_t *)client->data)->data)
#define TEAM(node) ((team_t *)node->data)
#define EGG(node) ((egg_t *)node->data)
#define DRONE(node) ((drone_t *)node->data)
#define PLAYER(node) ((ai_t *)node->data)
#define AI(node) ((ai_t *)&((zappy_client_t *)node->data)->data.ai)
#define AI_CLIENT(client) ((ai_t *)&ZAPPY_CLIENT(client)->data.ai)
#define AI_NODE(node) ((ai_t *)(node)->data)
#define GUI(node) ((gui_t *)&((zappy_client_t *)node->data)->data.gui)
#define INCANTATION(node) ((incantation_t *)node->data)

typedef enum ressources_s {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} ressources_t;

static const float ressource_density[] = {
    0.5,
    0.3,
    0.15,
    0.1,
    0.1,
    0.08,
    0.05
};

typedef struct coord_s {
    int x;
    int y;
} coord_t;

typedef enum direction_s {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
} direction_t;

typedef struct inventory_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} inventory_t;

typedef struct map_s {
    int width;
    int height;
    inventory_t **tiles;
} map_t;

typedef struct drone_s {
    coord_t coords;
    uint8_t level;
    inventory_t inventory;
    direction_t direction;
} drone_t;

typedef struct egg_s {
    size_t egg_id;
    ssize_t parent_id;
    coord_t coords;
    bool is_mature;
    struct timeval incubation_duration;
    struct timeval incubation_timer;
} egg_t;

typedef struct team_s {
    const char *name;
    tail_t eggs;
    uint16_t nb_matures_eggs;
    head_t drones;
    uint16_t nb_drones;
} team_t;

typedef struct ai_s {
    struct timeval command_timer;
    struct timeval food_timer;
    struct timeval food_duration;
    size_t player_id;
    tail_t commands;
    uint8_t nb_commands;
    drone_t *drone;
    team_t *team;
    node_t *client;
    bool incantating;
    bool alive;
} ai_t;

typedef struct gui_s {
    node_t *client;
} gui_t;

typedef enum {
    AI,
    GUI
} client_type;

typedef union zappy_client_data_s {
    ai_t ai;
    gui_t gui;
} zappy_client_data_t;

typedef struct zappy_client_s {
    client_type type;
    zappy_client_data_t data;
} zappy_client_t;

typedef struct incantation_requirement_s {
    uint8_t level;
    uint16_t nb_playes;
    inventory_t ressources;
} incantation_requirement_t;

typedef struct incantation_s {
    uint8_t level;
    head_t players;
    coord_t coords;
    struct timeval timer;
    struct timeval duration;
} incantation_t;

typedef enum game_state_s {
    LOADING,
    RUNNING,
    PAUSE,
    END
} game_state_t;

typedef struct zappy_server_s {
    uint8_t width;
    uint8_t height;
    uint8_t clients_nb;
    uint16_t freq;
    uint8_t teams_nb;
    server_t server;
    struct timeval timeout;
    struct timeval refill_timer;
    struct timeval refill_duration;
    struct timeval game_timer;
    bool first_ai;
    bool time_out_needed;
    bool display_eggs;
    map_t *map;
    inventory_t *global_inventory;
    head_t teams;
    head_t incantations;
    head_t players;
    head_t guis;
    game_state_t state;
} zappy_server_t;

// @brief create a map
// @param width width of the map
// @param height height of the map
// @return map_t* pointer to the map
void create_map(zappy_server_t *infos, int width, int height);

// @brief print the map
// @param map map to print
void print_map(map_t *map);

// @brief free the map
// @param map map to free
void free_map(map_t *map);

// @brief refill the map with available ressources
// @param infos server infos
// @param map map to refill
void refill_map(zappy_server_t *infos, map_t *map);

// @brief add nb ressources to tile
// @param infos server infos
// @param map_tile  tile to add ressources to
// @param nb  number of ressources to add
// @param r  ressource to add
void add_ressources_to_tile(
zappy_server_t *infos, inventory_t *map_tile, int nb, ressources_t r);

// @brief remove nb ressources from tile
// @param infos server infos
// @param m_tile map tile to remove ressources from
// @param nb number of ressources to remove
// @param r ressource to remove
void remove_ressources_from_tile(
zappy_server_t *infos, inventory_t *m_tile, int nb, ressources_t r);

void remove_ressources(zappy_server_t *zappy_server, const coord_t *coords,
    const inventory_t *ressouces);

// Utils rand :

void get_random_coord(int width, int height, coord_t *dest);
int get_random_int(int min, int max);
int get_random_direction(void);

// Args parser management :

bool get_uchar_value(const char *source, uint8_t *dest, long min, long max);
bool get_ushort_value(const char *source, uint16_t *dest, long min, long max);
bool get_teams(zappy_server_t *zappy_server, int argc,
    char *const *argv);

bool get_opt(zappy_server_t *zappy_server, int opt,
    int argc, char *const *argv);

bool parse_opt(zappy_server_t *zappy_client,
    int argc, char *const *argv);

// Teams management :

void free_team(node_t *team);
void free_teams(head_t *teams);

void display_team(node_t *team);
void display_teams(head_t *teams);

egg_t *get_mature_egg(team_t *team);
drone_t *new_drone(team_t *team, const coord_t *coords);
egg_t *new_egg(zappy_server_t *zappy_server, team_t *team,
    const coord_t *coords, ssize_t parent_id);
node_t *create_team(zappy_server_t *zappy_server, const char *name);

// Egg management :

tail_node_t *create_egg(zappy_server_t *zappy_server,
    const coord_t *coords, ssize_t parent_id);

// Drones management :

node_t *create_drone(const coord_t *coords);

// AI management :

void free_ai(node_t *ai);
void free_ais(head_t *ais);

// GUIS management :

void free_guis(head_t *guis);

// Incantation management :

extern const incantation_requirement_t incantation_requirements[];

bool check_required_ressourcies(zappy_server_t *zappy_server,
    const incantation_requirement_t *requirements, const coord_t *coords);

void remove_from_incantations(zappy_server_t *zappy_server, ai_t *ai);

bool insert_incantation(zappy_server_t *zappy_server,
    incantation_t *incantation);

void free_incantating_player(node_t *player_id);
void free_incantations(zappy_server_t *zappy_server);

void handle_post_incantation(zappy_server_t *zappy_server,
    incantation_t *incantation);

void handle_incantations(zappy_server_t *zappy_server,
    const struct timeval *now);

incantation_t *create_incantation(zappy_server_t *zappy_server,
    uint8_t level, const coord_t *coords);

// Server management :

void update_all_timers(zappy_server_t *zappy_server,
    const struct timeval *now);

bool check_time_limit(struct timeval *timer, struct timeval *duration,
    const struct timeval *now);
void update_timeout(zappy_server_t *zappy_server,
    const struct timeval *duration);
void calculate_duration(struct timeval *dest,
    uint16_t time_limit, uint16_t freq);

bool close_zappy_server(zappy_server_t *zappy_server);
bool init_zappy_server(zappy_server_t *zappy_server);
bool zappy_server_management(zappy_server_t *zappy_server);
