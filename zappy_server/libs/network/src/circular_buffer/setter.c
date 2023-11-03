/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** setter
*/

#include "circular_buffer.h"

void inc_read(circular_buffer_t *buffer)
{
    ++buffer->read;
    buffer->read %= BUFFLEN;
}

void dec_read(circular_buffer_t *buffer)
{
    if (!buffer->read)
        buffer->read = BUFFLEN;
    --buffer->read;
}

void inc_write(circular_buffer_t *buffer)
{
    ++buffer->write;
    buffer->write %= BUFFLEN;
}

void dec_write(circular_buffer_t *buffer)
{
    if (!buffer->write)
        buffer->write = BUFFLEN;
    --buffer->write;
}

void set_head(uint16_t *head, uint16_t index)
{
    *head = index % BUFFLEN;
}
