/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** communication
*/

#include "comminucation.h"

static bool handle_write(communicator_t *communicator,
    tail_node_t *current, const tail_node_t *next)
{
    char *extract = NULL;
    uint16_t len_extract;

    if (!(extract = extract_buffer(BUFFER(current), &len_extract)))
            return false;
    if (write(communicator->socket, extract, len_extract) <= 0) {
        MY_FREE(extract);
        ERROR("Failed to write", false);
    }
    MY_FREE(extract);
    if (!next) {
        set_head(&BUFFER(current)->read,
            BUFFER(current)->read + len_extract);
        return false;
    }
    TAILQ_REMOVE(&communicator->write, current, entries);
    MY_FREE(current->data);
    MY_FREE(current);
    return true;
}

void write_to_peer(communicator_t *communicator)
{
    tail_node_t *current = NULL;
    tail_node_t *entry = NULL;

    entry = TAILQ_FIRST(&communicator->write);
    while (entry) {
        current = entry;
        entry = TAILQ_NEXT(entry, entries);
        if (!handle_write(communicator, current, entry))
            return;
    }
}

bool read_from_peer(communicator_t *communicator)
{
    char buff[BUFFLEN] = {};
    ssize_t bytes;

    bytes = read(communicator->socket, &buff, BUFFLEN);
    if (bytes <= 0)
        return false;
    enqueue_message(communicator, READ, buff, bytes);
    return true;
}

bool is_communication_empty(communicator_t *communicator, com_type_t type)
{
    tail_t *buffers = (type == READ ? &communicator->read :
        &communicator->write);

    if (TAILQ_EMPTY(buffers) || is_empty(BUFFER(TAILQ_FIRST(buffers))))
        return true;
    return false;
}
