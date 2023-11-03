/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** comminucation
*/

#pragma once

#include <stdarg.h>

#include "circular_buffer.h"
#include "linked_list.h"

typedef enum {
    READ,
    WRITE
} com_type_t;

typedef struct communicator_s {
    int socket;
    tail_t read;
    tail_t write;
} communicator_t;

tail_node_t *new_circular_buffer(tail_t *circular_buffers);
void enqueue_message(communicator_t *communicator, com_type_t type,
    const char *message, size_t bytes);
void v_enqueue_messages(communicator_t *communicator, com_type_t type,
    va_list args);
void enqueue_messages(communicator_t *communicator, com_type_t type, ...);

void write_to_peer(communicator_t *communicator);
bool read_from_peer(communicator_t *communicator);
bool is_communication_empty(communicator_t *communicator, com_type_t type);
