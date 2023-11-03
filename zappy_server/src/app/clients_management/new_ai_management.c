/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** new_ai_management
*/

#include "zappy_server.h"
#include "ai_messages.h"
#include "protocol.h"
#include "gui.h"
#include "ai.h"

static void init_new_ai(zappy_client_t *new_ai, drone_t *drone,
    team_t *team, node_t *client)
{
    static unsigned int player_id = 0;

    new_ai->type = AI;
    gettimeofday(&new_ai->data.ai.food_timer, NULL);
    new_ai->data.ai.player_id = player_id++;
    TAILQ_INIT(&new_ai->data.ai.commands);
    new_ai->data.ai.nb_commands = 0;
    new_ai->data.ai.drone = drone;
    new_ai->data.ai.drone->inventory.food = START_FOOD;
    new_ai->data.ai.team = team;
    new_ai->data.ai.client = client;
    new_ai->data.ai.incantating = false;
    new_ai->data.ai.alive = true;
}

static node_t *create_ai(zappy_server_t *zappy_server, drone_t *drone,
    team_t *team, node_t *client)
{
    node_t *ai_node = NULL;
    zappy_client_t *new_ai = NULL;

    if (!(ai_node = malloc(sizeof(*ai_node))))
        ERROR("AI memory allocation failed", NULL);
    if (!(new_ai = malloc(sizeof(*new_ai)))) {
        MY_FREE(ai_node);
        ERROR("Failed to creat new ai client.", NULL);
    }
    init_new_ai(new_ai, drone, team, client);
    calculate_duration(&new_ai->data.ai.food_duration, START_FOOD_TIME,
        zappy_server->freq);
    ai_node->data = new_ai;
    CLIENT(client)->data = ai_node;
    CLIENT(client)->release_data = &ai_disconnection;
    return ai_node;
}

void handle_new_ai_client(zappy_server_t *zappy_server,
    node_t *client, team_t *team)
{
    egg_t *egg = NULL;
    drone_t *drone = NULL;
    node_t *ai_node = NULL;

    if (!(egg = get_mature_egg(team)) ||
        !(drone = new_drone(team, &egg->coords)) ||
        !(ai_node = create_ai(zappy_server, drone, team, client))) {
        MY_FREE(egg);
        MY_FREE(drone);
        enqueue_messages(&CLIENT(client)->communicator,
            WRITE, AI_KO CRLF, NULL);
        ERROR("Failed to creat new ai client.",);
    }
    if (!zappy_server->first_ai) {
        zappy_server->first_ai = true;
        gettimeofday(&zappy_server->game_timer, NULL);
    }
    LIST_INSERT_HEAD(&zappy_server->players, ai_node, entries);
    send_ai_connection_infos(zappy_server, team, ai_node, egg);
    MY_FREE(egg);
}
