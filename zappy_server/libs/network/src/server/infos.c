/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** infos
*/

#include "server.h"

void display_client_connection(client_t *client)
{
    char *client_ip = NULL;

    if (!(client_ip = inet_ntoa(client->addr.sin_addr))) {
        MY_FREE(client);
        PERROR("inet_ntoa failed", );
    }
    printf(
    "Connection from %s:%hu\n", client_ip, ntohs(client->addr.sin_port));
}
