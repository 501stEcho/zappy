/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** circular_buffer
*/

#include "circular_buffer.h"

circular_buffer_t *init_buffer(void)
{
    circular_buffer_t *new = NULL;

    if (!(new = malloc(sizeof(*new))))
        return NULL;
    new->read = 0;
    new->write = 0;
    return new;
}

bool is_empty(const circular_buffer_t *buffer)
{
    if (buffer->read == buffer->write)
        return true;
    return false;
}

bool is_full(const circular_buffer_t *buffer)
{
    uint16_t write = (buffer->write + 1) % BUFFLEN;

    if (buffer->read == write)
        return true;
    return false;
}

char read_buffer(circular_buffer_t *buffer)
{
    char value;

    if (buffer->read == buffer->write)
        return -1;
    value = buffer->buffer[buffer->read++];
    buffer->read %= BUFFLEN;
    return value;
}

uint16_t write_buffer(circular_buffer_t *buffer,
    const char *bytes, ssize_t len)
{
    uint16_t split = 0;
    uint16_t free_space = BUFFLEN - get_len(buffer) - 1;

    if (len > free_space)
        len = free_space;
    if (len <= (BUFFLEN - buffer->write)) {
        memmove(&buffer->buffer[buffer->write], bytes, len);
        buffer->write += len;
        buffer->write %= BUFFLEN;
        return len;
    }
    split = BUFFLEN - buffer->write;
    memmove(&buffer->buffer[buffer->write], bytes, split);
    buffer->write = 0;
    memmove(&buffer->buffer[buffer->write], &bytes[split], len - split);
    buffer->write += len - split;
    buffer->write %= BUFFLEN;
    return len;
}
