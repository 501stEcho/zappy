/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** tests_circular_buffers
*/
#include <criterion/criterion.h>

#include "circular_buffer.h"

Test(circular_buffer, write_in_buffer)
{
    circular_buffer_t buffer = {};
    const char *str = "Hello world\n";

    write_buffer(&buffer, "Hello world\n", 12);
    for (uint16_t i = 0; str[i]; ++i)
        cr_assert_eq(str[i], read_buffer(&buffer));
    set_head(&buffer.read, buffer.read + 5);
    cr_assert_eq(write_buffer(&buffer, "To long test", 12), 4);
}

Test(circular_buffer, write_in_buffer_circular)
{
    circular_buffer_t buffer = {};
    const char *str = "Hello world\n";

    set_head(&buffer.read, BUFFLEN - 2);
    set_head(&buffer.write, BUFFLEN - 2);
    write_buffer(&buffer, "Hello world\n", 12);
    for (uint16_t i = 0; str[i]; ++i)
        cr_assert_eq(str[i], read_buffer(&buffer));
}

Test(circular_buffer, is_buffer_full)
{
    circular_buffer_t buffer = {};


    cr_assert_eq(read_buffer(&buffer), -1);
    inc_read(&buffer);
    cr_assert_eq(is_full(&buffer), true);
}
