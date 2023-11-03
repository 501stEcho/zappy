/*
** EPITECH PROJECT, 2023
** B-NWP-400-LYN-4-1-myteams-anthony.faure
** File description:
** commande
*/

#pragma once

#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "my.h"
#include "linked_list.h"

#define WHITE_SPACES " \t"

#define QUOTE "\""

#define DELIM WHITE_SPACES QUOTE

typedef struct command_s {
    char **segments;
    uint16_t nb_segments;
} command_t;

void free_token(node_t *node);
node_t *create_token(char *token);
char *extract_token(char **reader);

void free_command(command_t *command);

command_t *get_command(char *buffer);
