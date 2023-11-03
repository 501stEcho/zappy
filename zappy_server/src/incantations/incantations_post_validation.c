/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** incantation_post_validation
*/

#include "gui.h"
#include "protocol.h"
#include "ai_messages.h"
#include "zappy_server.h"

static void incantation_failure(zappy_server_t *zappy_server,
    incantation_t *incantation)
{
    node_t *player_node = NULL;

    LIST_FOREACH(player_node, &incantation->players, entries)
        if (AI_NODE(player_node)->alive && AI_NODE(player_node)->client) {
            AI_NODE(player_node)->incantating = false;
            gettimeofday(&AI_NODE(player_node)->command_timer, NULL);
            enqueue_messages(
                &CLIENT(AI_NODE(player_node)->client)->communicator,
                WRITE, AI_KO CRLF, NULL);
        }
    pie_all(zappy_server, incantation->coords.x, incantation->coords.y, false);
}

static void elevation_check(zappy_server_t *zappy_server,
    incantation_t *incantation, ai_t *ai, const char *message)
{
    ai->incantating = false;
    gettimeofday(&ai->command_timer, NULL);
    if ((ai->drone->coords.x == incantation->coords.x) &&
        (ai->drone->coords.y == incantation->coords.y)) {
        ++ai->drone->level;
        enqueue_messages(&CLIENT(ai->client)->communicator, WRITE,
            message, CRLF, NULL);
        plv_all(zappy_server, ai->player_id);
    } else {
        enqueue_messages(&CLIENT(ai->client)->communicator, WRITE,
            AI_KO CRLF, NULL);
    }
}

static void incantation_success(zappy_server_t *zappy_server,
    incantation_t *incantation)
{
    node_t *player_node = NULL;
    char *message = NULL;

    asprintf(&message, "%s %hu", INCANTATION_END_MESSAGE,
        incantation->level + 1);
    LIST_FOREACH(player_node, &incantation->players, entries) {
        if (!AI_NODE(player_node)->alive || !AI_NODE(player_node)->client)
            continue;
        AI_NODE(player_node)->incantating = false;
        gettimeofday(&AI_NODE(player_node)->command_timer, NULL);
        elevation_check(zappy_server, incantation,
            AI_NODE(player_node), message);
    }
    pie_all(zappy_server, incantation->coords.x, incantation->coords.y, true);
    MY_FREE(message);
}

static uint16_t get_post_incantation_players(incantation_t *incantation)
{
    node_t *player_node = NULL;
    uint16_t nb_players = 0;

    LIST_FOREACH(player_node, &incantation->players, entries)
        if (AI_NODE(player_node)->alive && AI_NODE(player_node)->client &&
            AI_NODE(player_node)->drone->coords.x == incantation->coords.x &&
            AI_NODE(player_node)->drone->coords.y == incantation->coords.y)
            ++nb_players;
    return nb_players;
}

void handle_post_incantation(zappy_server_t *zappy_server,
    incantation_t *incantation)
{
    const incantation_requirement_t *requirements =
    &incantation_requirements[incantation->level - 1];

    if (!check_required_ressourcies(zappy_server, requirements,
        &incantation->coords) ||
        ((get_post_incantation_players(incantation) <
        requirements->nb_playes))) {
        incantation_failure(zappy_server, incantation);
    } else {
        incantation_success(zappy_server, incantation);
        remove_ressources(zappy_server, &incantation->coords,
            &requirements->ressources);
        bct_all(zappy_server, incantation->coords.x, incantation->coords.y);
    }
}
