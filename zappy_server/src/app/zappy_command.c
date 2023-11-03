/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** zappy_command
*/

#include "zappy_server.h"
#include "protocol.h"

static void exec_command(zappy_server_t *zappy_server, client_t *client,
    const command_handler_t *handler, command_t *command)
{
    if ((command->nb_segments - 1) != handler->nb_args) {
        printf("[%s] : Invalid number of args, expected %hu but got %hu.\n",
        handler->mnemonique, handler->nb_args, command->nb_segments - 1);
        if (client)
            enqueue_messages(&client->communicator, WRITE,
                ZAPPY_CLIENT(client)->type == AI ? AI_KO : GUI_PARAMETER,
                    CRLF, NULL);
        free_command(command);
        return;
    }
    handler->handler(zappy_server, client, command);
    free_command(command);
}

static command_t *get_valid_command(char *buffer)
{
    command_t *command = get_command(buffer);

    if (!command)
        ERROR("Failed to parse the command.", NULL);
    if (!command->nb_segments) {
        printf("Empty command.\n");
        free_command(command);
        return NULL;
    }
    return command;
}

void handle_command(zappy_server_t *zappy_server, client_t *client,
    char *buffer, const command_handler_t command_tab[])
{
    command_t *command = get_valid_command(buffer);

    if (!command) {
        if (client)
            enqueue_messages(&client->communicator, WRITE,
                ZAPPY_CLIENT(client)->type == AI ? AI_KO : GUI_UNKNOWN,
                CRLF, NULL);
        ERROR("Failed to get the command.", );
    }
    for (uint16_t i = 0; command_tab[i].mnemonique; ++i)
        if (!strcmp(command_tab[i].mnemonique, command->segments[0]))
            return exec_command(zappy_server, client, &command_tab[i], command);
    printf("Unknown command %s\n", command->segments[0]);
    if (client)
        enqueue_messages(&client->communicator, WRITE,
            ZAPPY_CLIENT(client)->type == AI ? AI_KO : GUI_UNKNOWN,
                CRLF, NULL);
    free_command(command);
}

void handle_unkown_user_command(zappy_server_t *zappy_server,
    node_t *client, char *buffer)
{
    command_t *command = get_command(buffer);

    if (!command) {
        enqueue_messages(&CLIENT(client)->communicator,
            WRITE, KO CRLF, NULL);
        ERROR("Failed to parse the command.",);
    }
    if (!command->nb_segments || (command->nb_segments != 1)) {
        enqueue_messages(&CLIENT(client)->communicator,
            WRITE, KO CRLF, NULL);
        if (command->nb_segments == 1)
            printf("Empty command.\n");
        return free_command(command);;
    }
    handle_client_type(zappy_server, client, command->segments[0]);
    free_command(command);
}

void handle_user_command(zappy_server_t *zappy_server,
    client_t *client, char *buffer)
{
    switch (ZAPPY_CLIENT(client)->type) {
        case AI:
            if (AI_CLIENT(client)->alive)
                enqueue_command(zappy_server, client, buffer);
            break;
        case GUI:
            handle_command(zappy_server, client, buffer, gui_commands);
            break;
        default:
            enqueue_messages(&client->communicator, WRITE, KO CRLF, NULL);
            ERROR("Unkown client type.",);
    }
}
