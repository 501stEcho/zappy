/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** main
*/
#include "zappy_server.h"
#include "infos.h"

static void usage(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height "
        "-n name1 name2 ... -c clientsNb -f freq --auto-start on|off"
        " --display-eggs true|false\n");
    printf("\tport\t\tis the port number\n");
    printf("\twidth\t\tis the width of the world\n");
    printf("\theight\t\tis the height of the world\n");
    printf("\tnameX\t\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\t\tis the reciprocal of time unit " \
        "for execution of actions\n");
    printf("\tauto-start\tdoes the greeting is send automaticly\n");
    printf("\tdisplay-eggs\teggs are visible and destructible\n");
}

static bool spawn_eggs(zappy_server_t *zappy_server)
{
    egg_t *egg = NULL;
    node_t *entry = NULL;
    coord_t coords = {};

    LIST_FOREACH(entry, &zappy_server->teams, entries)
    for (uint8_t i = 0; i < zappy_server->clients_nb; ++i) {
        get_random_coord(zappy_server->width, zappy_server->height, &coords);
        if (!(egg = new_egg(zappy_server, TEAM(entry), &coords, -1)))
            return false;
        egg->is_mature = true;
        ++TEAM(entry)->nb_matures_eggs;
    }
    return true;
}

static bool start_zappy_serveur(zappy_server_t *zappy_server,
    int ac, char *const *av)
{
    LIST_INIT(&zappy_server->teams);
    if (parse_opt(zappy_server, ac, av) == false) {
        usage();
        return false;
    }
    create_map(zappy_server, zappy_server->width, zappy_server->height);
    if (zappy_server->map == NULL)
        return false;
    if (!spawn_eggs(zappy_server)) {
        close_zappy_server(zappy_server);
        ERROR("Failed to make spawn the eggs", false);
    }
    if (!init_zappy_server(zappy_server)) {
        close_zappy_server(zappy_server);
        ERROR("Serveur initialisation failed.", false);
    }
    signal(SIGINT, &signal_handler);
    signal(SIGPIPE, SIG_IGN);
    display_zappy_server(zappy_server);
    return true;
}

int main(int argc, char *const *argv)
{
    zappy_server_t zappy_server = {.freq = DEFAULT_FREQ,
        .state = DEFAULT_STATE};

    srand(time(NULL));
    if (!start_zappy_serveur(&zappy_server, argc, argv))
        return 84;
    if (!zappy_server_management(&zappy_server)) {
        if (!close_zappy_server(&zappy_server))
            PERROR("Call to server closure : close failed.", 84);
        return 84;
    }
    if (!close_zappy_server(&zappy_server))
        PERROR("Call to server closure : close failed.", 84);
    return 0;
}
