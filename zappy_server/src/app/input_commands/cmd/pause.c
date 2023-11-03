/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** pause
*/

#include "zappy_server.h"
#include "protocol.h"

void pause_command(zappy_server_t *zappy_server,
    client_t *client __attribute__((unused)),
    command_t *command __attribute__((unused)))
{
    struct timeval now;

    switch (zappy_server->state ) {
        case LOADING:
            printf("The server can't be paused, it's not started\n");
            return;
        case RUNNING:
            zappy_server->state = PAUSE;
            printf("The server is now paused\n");
            return;
        case PAUSE:
            zappy_server->state = RUNNING;
            gettimeofday(&now, NULL);
            update_all_timers(zappy_server, &now);
            printf("The server is no longer paused\n");
            return;
        case END:
            printf("The server can not be paused, the party as ended.\n");
            return;
    }
}
