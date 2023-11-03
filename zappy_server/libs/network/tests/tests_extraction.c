/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** tests_circular_buffers
*/
#include <criterion/criterion.h>

#include "circular_buffer.h"
#include "comminucation.h"

Test(circular_buffer, extraction)
{
    communicator_t communicator = {};
    tail_node_t *buffer = NULL;
    char *extract = NULL;
    char str[] = "TEST\n";
    uint16_t len = 0;

    TAILQ_INIT(&communicator.read);
    TAILQ_INIT(&communicator.write);
    enqueue_messages(&communicator, READ, str, NULL);
    cr_assert_not_null((buffer = TAILQ_FIRST(&communicator.read)));
    extract = extract_buffer(BUFFER(buffer), &len);
    cr_assert_str_eq(extract, str);
    cr_assert_eq(len, strlen(str));
}
