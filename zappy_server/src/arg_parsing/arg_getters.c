/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** arg_getters
*/
#include "zappy_server.h"

bool get_uchar_value(const char *source, uint8_t *dest, long min, long max)
{
    char *end_ptr = NULL;
    long value = strtol(source, &end_ptr, 10);

    if (*end_ptr != '\0')
        ERROR("Invalid value given as dimension", false);
    if ((value < min) || (value > max)) {
        fprintf(stderr, "Value must be between %ld and %ld\n", min, max);
        return false;
    }
    *dest = value;
    return true;
}

bool get_ushort_value(const char *source, uint16_t *dest, long min, long max)
{
    char *end_ptr = NULL;
    long value = strtol(source, &end_ptr, 10);

    if (*end_ptr != '\0')
        ERROR("Invalid value given as dimension", false);
    if ((value < min) || (value > max)) {
        fprintf(stderr, "Value must be between %ld and %ld\n", min, max);
        return false;
    }
    *dest = value;
    return true;
}

bool get_teams(zappy_server_t *zappy_server, int argc,
    char *const *argv)
{
    node_t *team = NULL;

    --optind;
    while ((optind < argc) && (argv[optind][0] != '-')) {
        if (!(team = create_team(zappy_server, argv[optind]))) {
            free_teams(&zappy_server->teams);
            ERROR("Team creation failed", false);
        }
        LIST_INSERT_HEAD(&zappy_server->teams, team, entries);
        ++zappy_server->teams_nb;
        ++optind;
    }
    return true;
}
