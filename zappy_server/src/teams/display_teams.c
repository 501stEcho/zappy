/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** display_teams
*/
#include "zappy_server.h"

void display_team(node_t *team)
{
    printf("name : [%s]\n", TEAM(team)->name);
    printf("nb_drones : [%hu]\n", TEAM(team)->nb_drones);
    printf("nb_matures_eggs : [%hu]\n", TEAM(team)->nb_matures_eggs);
}

void display_teams(head_t *teams)
{
    apply_list(teams, &display_team);
}
