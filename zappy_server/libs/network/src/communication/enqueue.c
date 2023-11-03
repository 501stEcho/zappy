/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** enqueue
*/

#include "comminucation.h"

tail_node_t *new_circular_buffer(tail_t *circular_buffers)
{
    circular_buffer_t *new_circular_buffer = init_buffer();
    tail_node_t *buffer_node = NULL;

    if (!new_circular_buffer)
        ERROR("Failed to create new circulare buffer", NULL);
    if (!(buffer_node = malloc(sizeof(*buffer_node)))) {
        MY_FREE(new_circular_buffer);
        ERROR("Failed to create new circulare buffer node", NULL);
    }
    buffer_node->data = new_circular_buffer;
    TAILQ_INSERT_TAIL(circular_buffers, buffer_node, entries);
    return buffer_node;
}

void enqueue_message(communicator_t *communicator, com_type_t type,
    const char *message, size_t bytes)
{
    uint16_t enqueued = 0;
    tail_t *circular_buffers = (type == READ ? &communicator->read :
        &communicator->write);
    tail_node_t *buffer_node = NULL;

    if (TAILQ_EMPTY(circular_buffers) && !new_circular_buffer(circular_buffers))
        ERROR("Faild to create new buffer",);
    buffer_node = TAILQ_FIRST(circular_buffers);
    while (bytes) {
        if (is_full(BUFFER(buffer_node)) &&
            !(buffer_node = TAILQ_NEXT(buffer_node, entries)) &&
            !(buffer_node = new_circular_buffer(circular_buffers)))
                ERROR("Faild to create new buffer",);
        enqueued = write_buffer(BUFFER(buffer_node), message, bytes);
        message += enqueued;
        bytes -= enqueued;
    }
}

void v_enqueue_messages(communicator_t *communicator, com_type_t type,
    va_list args)
{
    const char *message = NULL;

    while ((message = va_arg(args, const char *)))
        enqueue_message(communicator, type, message, strlen(message));
}

void enqueue_messages(communicator_t *communicator, com_type_t type, ...)
{
    const char *message = NULL;
    va_list args;

    va_start(args, type);
    while ((message = va_arg(args, const char *)))
        enqueue_message(communicator, type, message, strlen(message));
    va_end(args);
}
