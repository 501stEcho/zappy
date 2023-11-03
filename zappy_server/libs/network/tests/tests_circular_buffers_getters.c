/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** tests_circular_buffers_getters
*/

#include <criterion/criterion.h>

#include "circular_buffer.h"
#include "comminucation.h"

Test(circular_buffer, extract)
{
    circular_buffer_t buffer = {};
    char *extract = NULL;
    uint16_t len = 0;

    cr_assert_eq(extract_buffer(&buffer, &len), NULL);
    set_head(&buffer.read, BUFFLEN - 2);
    set_head(&buffer.write, BUFFLEN - 2);
    write_buffer(&buffer, "Hello world\n", 12);
    extract = extract_buffer(&buffer, &len);
    cr_assert_eq(len, strlen("Hello world\n"));
    cr_assert_str_eq(extract, "Hello world\n");
    free(extract);
}

Test(circular_buffer, realse_of_buffers)
{
    communicator_t communicator = {};
    char *extract = NULL;

    TAILQ_INIT(&communicator.read);
    TAILQ_INIT(&communicator.write);
    enqueue_message(&communicator, READ, "Test of extraction", 18);
    cr_assert_null(extract_until(&communicator.read, "invalid"));
    extract = extract_until(&communicator.read, "tion");
    cr_assert_str_eq(extract, "Test of extrac");
    free(extract);
    inc_read(BUFFER(TAILQ_FIRST(&communicator.read)));
    enqueue_message(&communicator, READ, "Test of extraction", 18);
    extract = extract_until(&communicator.read, "tion");
    cr_assert_str_eq(extract, "Test of extrac");
    free(extract);
}
