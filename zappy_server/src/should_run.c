/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** should_run
*/

#include "server.h"

void signal_handler(int sig)
{
    (void)sig;
    (*is_running()) = false;
}

bool *is_running(void)
{
    static bool should_run = true;

    return &should_run;
}
