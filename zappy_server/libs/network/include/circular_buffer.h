/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** circular_buffer
*/

#pragma once

#define _GNU_SOURCE

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linked_list.h"
#include "my.h"

#define BUFFER(node) ((circular_buffer_t *)node->data)

#define BUFFLEN 4096

typedef struct circular_buffer_s {
    uint16_t read;
    uint16_t write;
    char buffer[BUFFLEN];
} circular_buffer_t;

circular_buffer_t *init_buffer(void);
bool is_empty(const circular_buffer_t *buffer);
bool is_full(const circular_buffer_t *buffer);
char read_buffer(circular_buffer_t *buffer);
uint16_t write_buffer(circular_buffer_t *buffer,
    const char *bytes, ssize_t len);

void inc_read(circular_buffer_t *buffer);
void dec_read(circular_buffer_t *buffer);
void inc_write(circular_buffer_t *buffer);
void dec_write(circular_buffer_t *buffer);
void set_head(uint16_t *head, uint16_t index);

uint16_t get_len(const circular_buffer_t *buffer);
char *extract_buffer(circular_buffer_t *buffer, uint16_t *len);
char *extract_until(tail_t *circular_buffers, const char *motif);
