/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** input_protocol
*/

#include "zappy_server.h"
#include "protocol.h"

const command_handler_t input_commands[] = {
    {.mnemonique = "/clients", .handler = &clients_command, .nb_args = 0},
    {.mnemonique = "/quit", .handler = &quit_command, .nb_args = 0},
    {.mnemonique = "/send_ais", .handler = &send_ais_command, .nb_args = 1},
    {.mnemonique = "/send_guis", .handler = &send_guis_command, .nb_args = 1},
    {.mnemonique = "/map", .handler = &map_command, .nb_args = 0},
    {.mnemonique = "/clear", .handler = &clear_command, .nb_args = 0},
    {.mnemonique = "/pause", .handler = &pause_command, .nb_args = 0},
    {.mnemonique = "/start", .handler = &start_command, .nb_args = 0},
    {}
};

void handle_input_command(zappy_server_t *zappy_server)
{
    char *buffer = NULL;

    if ((buffer = extract_until(&zappy_server->server.communicator.read, CRLF)))
        handle_command(zappy_server, NULL, buffer, input_commands);
    MY_FREE(buffer);
}
