/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** incantation_validation
*/

#include "zappy_server.h"
#include "protocol.h"

const incantation_requirement_t incantation_requirements[] = {
    {.level = 1, .nb_playes = 1,
        .ressources = {
            .linemate = 1
        }
    },
    {.level = 2, .nb_playes = 2,
        .ressources = {
            .linemate = 1,
            .deraumere = 1
        }
    },
    {.level = 3, .nb_playes = 2,
        .ressources = {
            .linemate = 2,
            .sibur = 1,
            .phiras = 2
        }
    },
    {.level = 4, .nb_playes = 4,
        .ressources = {
            .linemate = 1,
            .deraumere = 1,
            .sibur = 2,
            .phiras = 1
        }
    },
    {.level = 5, .nb_playes = 4,
        .ressources = {
            .linemate = 1,
            .deraumere = 2,
            .sibur = 1,
            .mendiane = 3
        }
    },
    {.level = 6, .nb_playes = 6,
        .ressources = {
            .linemate = 1,
            .deraumere = 2,
            .sibur = 3,
            .phiras = 1
        }
    },
    {.level = 7, .nb_playes = 6,
        .ressources = {
            .linemate = 2,
            .deraumere = 2,
            .sibur = 2,
            .mendiane = 2,
            .phiras = 2,
            .thystame = 1
        }
    },
    {}
};

bool check_required_ressourcies(zappy_server_t *zappy_server,
    const incantation_requirement_t *requirements, const coord_t *coords)
{
    if ((zappy_server->map->tiles[coords->y][coords->x].linemate <
            requirements->ressources.linemate) ||
        (zappy_server->map->tiles[coords->y][coords->x].deraumere <
            requirements->ressources.deraumere) ||
        (zappy_server->map->tiles[coords->y][coords->x].sibur <
            requirements->ressources.sibur) ||
        (zappy_server->map->tiles[coords->y][coords->x].mendiane <
            requirements->ressources.mendiane) ||
        (zappy_server->map->tiles[coords->y][coords->x].phiras <
            requirements->ressources.phiras) ||
        (zappy_server->map->tiles[coords->y][coords->x].thystame <
            requirements->ressources.thystame))
            return false;
    return true;
}

void handle_incantations(zappy_server_t *zappy_server,
    const struct timeval *now)
{
    node_t *entry = NULL;
    node_t *current = NULL;

    entry = LIST_FIRST(&zappy_server->incantations);
    while (entry) {
        current = entry;
        entry = LIST_NEXT(entry, entries);
        if (check_time_limit(&INCANTATION(current)->timer,
            &INCANTATION(current)->duration, now)) {
            handle_post_incantation(zappy_server, INCANTATION(current));
            LIST_REMOVE(current, entries);
            free_list(&INCANTATION(current)->players, &free_incantating_player);
            MY_FREE(current->data);
            MY_FREE(current);
        } else {
            gettimeofday(&INCANTATION(current)->timer, NULL);
            update_timeout(zappy_server, &INCANTATION(current)->duration);
        }
    }
}
