/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** ai_food
*/

#include "zappy_server.h"
#include "ai_messages.h"
#include "protocol.h"
#include "gui.h"
#include "ai.h"

void handle_ai_food(zappy_server_t *zappy_server, client_t *client,
    const struct timeval *now)
{
    if (check_time_limit(&AI_CLIENT(client)->food_timer,
        &AI_CLIENT(client)->food_duration, now)) {
        if (!AI_CLIENT(client)->drone->inventory.food) {
            enqueue_messages(&client->communicator, WRITE,
                AI_DEAD CRLF, NULL);
            pdi_all(zappy_server, AI_CLIENT(client)->player_id);
            AI_CLIENT(client)->alive = false;
            return;
        }
        --AI_CLIENT(client)->drone->inventory.food;
        calculate_duration(&AI_CLIENT(client)->food_duration, START_FOOD_TIME,
            zappy_server->freq);
        gettimeofday(&AI_CLIENT(client)->food_timer, NULL);
        pin_all(zappy_server, AI_CLIENT(client)->player_id);
    }
    update_timeout(zappy_server, &AI_CLIENT(client)->food_duration);
}
