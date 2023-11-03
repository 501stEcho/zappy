/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** arg_parsing
*/
#include "zappy_server.h"
static const struct option long_options[] = {
    {.name = "help", .has_arg = no_argument, .flag = NULL, .val = 'd'},
    {.name = "auto-start", .has_arg = required_argument,
        .flag = NULL, .val = 's'},
    {.name = "display-eggs", .has_arg = required_argument,
        .flag = NULL, .val = 'e'},
    {}
};

bool parse_opt(zappy_server_t *zappy_server, int argc, char *const *argv)
{
    int opt = 0;

    while ((opt = getopt_long(argc, argv, "p:x:y:n:c:f:s:e:",
        long_options, NULL)) > 0) {
        if (!get_opt(zappy_server, opt, argc, argv)) {
            free_teams(&zappy_server->teams);
            return false;
        }
    }
    if (optind < argc) {
        free_teams(&zappy_server->teams);
        ERROR("Unexpected values are passed as parameter", false);
    }
    if ((zappy_server->server.port <= 0) || (zappy_server->width <= 0) ||
        (zappy_server->height <= 0) || !zappy_server->teams_nb ||
        (zappy_server->clients_nb <= 0) || (zappy_server->freq <= 0)) {
        free_teams(&zappy_server->teams);
        ERROR("Missing requiered minimal informations", false);
    }
    return true;
}
