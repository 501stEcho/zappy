/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** arg_parsing_next
*/
#include "zappy_server.h"

static bool get_opt_last(zappy_server_t *zappy_server, int opt)
{
    switch (opt) {
        case 'e':
            if (!strcmp(optarg, "true")) {
                zappy_server->display_eggs = true;
                return true;
            }
            if (!strcmp(optarg, "false")) {
                zappy_server->display_eggs = false;
                return true;
            }
            ERROR("Option -e invalid value", false);
        case '?':
        default: return false;
    }
}

static bool get_opt_next(zappy_server_t *zappy_server, int opt)
{
    switch (opt) {
        case 's':
            if (!strcmp(optarg, "on")) {
                zappy_server->state = RUNNING;
                return true;
            }
            if (!strcmp(optarg, "off")) {
                zappy_server->state = LOADING;
                return true;
            }
            ERROR("Option -s invalid value", false);
        default: return get_opt_last(zappy_server, opt);
    }
}

static bool get_opt_rest(zappy_server_t *zappy_server, int opt,
    int argc, char *const *argv)
{
    switch (opt) {
        case 'c':
            if (!get_uchar_value(optarg, &zappy_server->clients_nb,
                MIN_CLIENTSNB, MAX_CLIENTSNB))
                ERROR("Option -c invalid value", false);
            return true;
        case 'f':
            if (!get_ushort_value(
                optarg, &zappy_server->freq, MIN_FREQ, MAX_FREQ))
                ERROR("Option -f invalid value", false);
            return true;
        case 'n':
            if (!get_teams(zappy_server, argc, argv))
                ERROR("Option -n invalid value", false);
            return true;
        default: return get_opt_next(zappy_server, opt);
    }
}

bool get_opt(zappy_server_t *zappy_server, int opt,
    int argc, char *const *argv)
{
    switch (opt) {
        case 'd': return false;
        case 'p':
            if (!get_ushort_value(optarg, &zappy_server->server.port,
                MIN_PORT, MAX_PORT))
                ERROR("Option -p invalid value", false);
            return true;
        case 'x':
            if (!get_uchar_value(optarg, &zappy_server->width, MIN_X, MAX_X))
                ERROR("Option -x invalid value", false);
            return true;
        case 'y':
            if (!get_uchar_value(optarg, &zappy_server->height, MIN_Y, MAX_Y))
                ERROR("Option -y invalid value", false);
            return true;
        default: return get_opt_rest(zappy_server, opt, argc, argv);
    }
}
