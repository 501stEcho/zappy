/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** display
*/

#include "zappy_server.h"
#include "infos.h"

void display_zappy_server(zappy_server_t *zappy_server)
{
    printf("===================Zappy Server===================\n");
    printf("port = %hu\n", zappy_server->server.port);
    printf("width = %hu\n", zappy_server->width);
    printf("height = %hu\n", zappy_server->height);
    printf("clients_nb = %hu\n", zappy_server->clients_nb);
    printf("freq = %hu\n", zappy_server->freq);
    printf("Teams [%hu]:\n", zappy_server->teams_nb);
    printf("display eggs = [%s]\n",
        zappy_server->display_eggs ? "true" : "false");
    display_teams(&zappy_server->teams);
    printf("==================================================\n");
}
