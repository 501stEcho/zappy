/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** free_teams
*/
#include "zappy_server.h"

static void free_egg(tail_node_t *egg)
{
    MY_FREE(egg->data);
    MY_FREE(egg);
}

static void free_drone(node_t *drone)
{
    MY_FREE(drone->data);
    MY_FREE(drone);
}

void free_team(node_t *team)
{
    free_tail(&TEAM(team)->eggs, &free_egg);
    free_list(&TEAM(team)->drones, &free_drone);
    MY_FREE(team->data);
    MY_FREE(team);
}

void free_teams(head_t *teams)
{
    free_list(teams, &free_team);
}
