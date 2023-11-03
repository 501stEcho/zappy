/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** client
*/

#include "zappy_server.h"
#include "protocol.h"
#include "infos.h"

void display_client(client_t *client)
{
    char *client_ip = NULL;

    printf("================USER================\n");
    if (!(client_ip = inet_ntoa(client->addr.sin_addr)))
        PERROR("inet_ntoa failed", );
    printf("%s:%hu\n", client_ip, ntohs(client->addr.sin_port));
    printf("Type = ");
    if (client->data) {
        switch (ZAPPY_CLIENT(client)->type) {
        case AI: printf("AI\n"); break;
        case GUI: printf("GUI\n"); break;
        default: printf("Unkown\n");
        }
    } else {
        printf("Unkown\n");
    }
    printf("====================================\n");
}

void apply_clients(head_t *clients, void (*func)(client_t *node))
{
    node_t *tmp = NULL;

    LIST_FOREACH(tmp, clients, entries)
    func(CLIENT(tmp));
    return;
}
