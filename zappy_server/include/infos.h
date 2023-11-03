/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** infos
*/

#pragma once

#include "protocol.h"

void display_client(client_t *client);
void apply_clients(head_t *clients, void (*func)(client_t *node));
void display_client_connection(client_t *client);

void display_zappy_server(zappy_server_t *zappy_server);
