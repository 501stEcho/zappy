/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** getter
*/

#include "circular_buffer.h"

uint16_t get_len(const circular_buffer_t *buffer)
{
    if (is_empty(buffer))
        return 0;
    if (buffer->read < buffer->write)
        return buffer->write - buffer->read;
    return (BUFFLEN - buffer->read) + buffer->write;
}

char *extract_buffer(circular_buffer_t *buffer, uint16_t *len)
{
    char *buff;
    uint16_t end;
    uint16_t begin;

    if (!(*len = get_len(buffer)))
        return NULL;
    if (buffer->read < buffer->write) {
        if (!(buff = malloc(sizeof(*buff) * (*len + 1))))
            return NULL;
        memmove(buff, &buffer->buffer[buffer->read], *len);
    } else {
        begin = BUFFLEN - buffer->read;
        end = buffer->write + 1;
        if (!(buff = malloc(sizeof(*buff) * (begin + end + 1))))
            return NULL;
        memmove(buff, &buffer->buffer[buffer->read], begin);
        memmove(&buff[begin], buffer->buffer, end);
    }
    buff[*len] = '\0';
    return buff;
}

static void release_buffers(tail_t *buffers, circular_buffer_t *buffer,
    size_t bytes)
{
    uint16_t bytes_to_remove = bytes % BUFFLEN;
    tail_node_t *current = NULL;
    tail_node_t *entry = NULL;

    entry = TAILQ_FIRST(buffers);
    while (entry) {
        current = entry;
        entry = TAILQ_NEXT(entry, entries);
        if (BUFFER(current) == buffer) {
            set_head(&buffer->read, buffer->read + bytes_to_remove);
            return;
        }
        TAILQ_REMOVE(buffers, current, entries);
        MY_FREE(current->data);
        MY_FREE(current);
    }
}

static char *extract_new_datas(char *datas, circular_buffer_t *buffer)
{
    uint16_t len_extract;
    char *new_datas = NULL;
    char *extract = NULL;

    if (!datas) {
        if (!(new_datas = extract_buffer(buffer, &len_extract)))
            return NULL;
    } else {
        if (!(extract = extract_buffer(buffer, &len_extract)))
            return NULL;
        asprintf(&new_datas, "%s%s", datas, extract);
        MY_FREE(extract);
    }
    return new_datas;
}

char *extract_until(tail_t *buffers, const char *motif)
{
    size_t len_result = 0;
    char *tmp = NULL;
    char *datas = NULL;
    char *founded_motif = NULL;
    tail_node_t *entry = NULL;
    TAILQ_FOREACH(entry, buffers, entries) {
        tmp = extract_new_datas(datas, BUFFER(entry));
        MY_FREE(datas);
        if (!tmp)
            return NULL;
        datas = tmp;
        if ((founded_motif = strstr(datas, motif))) {
            len_result = founded_motif - datas;
            datas[len_result] = '\0';
            release_buffers(buffers, BUFFER(entry), len_result + strlen(motif));
            return datas;
        }
    }
    MY_FREE(datas);
    return NULL;
}
