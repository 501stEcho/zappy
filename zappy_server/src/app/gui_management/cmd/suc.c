/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** msz
*/

#include "zappy_server.h"
#include "gui_messages.h"
#include "protocol.h"
#include "gui.h"

void suc_event(client_t *client)
{
    enqueue_messages(&client->communicator, WRITE,
        GUI_UNKNOWN CRLF, NULL);
}
