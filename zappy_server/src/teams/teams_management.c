/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** team_creation
*/

#include "zappy_server.h"

egg_t *get_mature_egg(team_t *team)
{
    egg_t *egg = NULL;
    tail_node_t *current = NULL;
    tail_node_t *entry = NULL;

    entry = TAILQ_FIRST(&team->eggs);
    while (entry) {
        current = entry;
        entry = TAILQ_NEXT(entry, entries);
        if (EGG(current)->is_mature) {
            TAILQ_REMOVE(&team->eggs, current, entries);
            egg = EGG(current);
            MY_FREE(current);
            --team->nb_matures_eggs;
            return egg;
        }
    }
    return NULL;
}

drone_t *new_drone(team_t *team, const coord_t *coords)
{
    node_t *drone_node = create_drone(coords);

    if (!drone_node)
        ERROR("Failed to create a drone", NULL);
    LIST_INSERT_HEAD(&team->drones, drone_node, entries);
    ++team->nb_drones;
    return drone_node->data;
}

egg_t *new_egg(zappy_server_t *zappy_server, team_t *team,
    const coord_t *coords, ssize_t parent_id)
{
    tail_node_t *egg_node = create_egg(zappy_server, coords, parent_id);

    if (!egg_node)
        ERROR("Failed to create an egg", NULL);
    TAILQ_INSERT_TAIL(&team->eggs, egg_node, entries);
    return egg_node->data;
}

static bool is_valid_team_name(zappy_server_t *zappy_server, const char *name)
{
    node_t *entry = NULL;

    if (!strlen(name))
        ERROR("Can create a team with an empty name", false);
    LIST_FOREACH(entry, &zappy_server->teams, entries)
        if (!strcmp(name, TEAM(entry)->name))
            ERROR("Can create two teams with the same name", false);
    return true;
}

node_t *create_team(zappy_server_t *zappy_server, const char *name)
{
    node_t *team_node = NULL;
    team_t *new_team = NULL;

    if (!is_valid_team_name(zappy_server, name))
        ERROR("Error at team creation", NULL);
    if (!(team_node = malloc(sizeof(*team_node))))
        PERROR("Team memory allocation failed", NULL);
    if (!(new_team = malloc(sizeof(*new_team)))) {
        MY_FREE(team_node);
        PERROR("Team memory allocation failed", NULL);
    }
    new_team->name = name;
    TAILQ_INIT(&new_team->eggs);
    new_team->nb_matures_eggs = 0;
    LIST_INIT(&new_team->drones);
    new_team->nb_drones = 0;
    team_node->data = new_team;
    return team_node;
}
