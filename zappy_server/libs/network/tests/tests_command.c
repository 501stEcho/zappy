/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** tests_command
*/

#include <criterion/criterion.h>

#include "command.h"

Test(command_tests, command_free)
{
    command_t *command = malloc(sizeof(*command));

    command->nb_segments = 1;
    command->segments = malloc(sizeof(*command->segments) * 1);
    command->segments[0] = strdup("Test");
    free_command(command);
}

Test(command_tests, create_command)
{
    command_t *command = NULL;

    command = get_command("Test  command   \t creation  ");
    free_command(command);
    command = get_command("");
    free_command(command);
}
