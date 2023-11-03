/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** inventory
*/

#include "zappy_server.h"
#include "protocol.h"
#include "ai.h"

char *get_inventory(inventory_t inventory)
{
    char *response = NULL;

    asprintf(&response, "[ food %d, linemate %d, deraumere %d, sibur %d, "
        "mendiane %d, phiras %d, thystame %d ]\n",
        inventory.food, inventory.linemate, inventory.deraumere,
        inventory.sibur, inventory.mendiane, inventory.phiras,
        inventory.thystame);
    return response;
}

void inventory_cmd(zappy_server_t *server __attribute__((unused)),
    client_t *client, command_t *cmd __attribute__((unused)))
{
    char *inventory = NULL;

    inventory = get_inventory(AI_CLIENT(client)->drone->inventory);
    enqueue_messages(&client->communicator, WRITE, inventory, NULL);
    MY_FREE(inventory);
}
