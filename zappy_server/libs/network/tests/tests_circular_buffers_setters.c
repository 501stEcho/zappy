/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** tests_circular_buffers_setters
*/

#include <criterion/criterion.h>

#include "circular_buffer.h"

Test(circular_buffer, increment_read_head)
{
    circular_buffer_t buffer = {};

    inc_read(&buffer);
    cr_assert_eq(buffer.read, 1);
}

Test(circular_buffer, decrement_read_head)
{
    circular_buffer_t buffer = {};

    dec_read(&buffer);
    cr_assert_eq(buffer.read, BUFFLEN - 1);
}

Test(circular_buffer, increment_write_head)
{
    circular_buffer_t buffer = {};

    inc_write(&buffer);
    cr_assert_eq(buffer.write, 1);
}

Test(circular_buffer, decrement_write_head)
{
    circular_buffer_t buffer = {};

    dec_write(&buffer);
    cr_assert_eq(buffer.write, BUFFLEN - 1);
}

Test(circular_buffer, set_head)
{
    circular_buffer_t buffer = {};

    set_head(&buffer.read, buffer.read + 10);
    cr_assert_eq(buffer.read, 10);
}
