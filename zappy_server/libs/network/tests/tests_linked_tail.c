/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** tests_linked_list
*/

#include <criterion/criterion.h>

#include "linked_list.h"

static void free_node(tail_node_t *node)
{
    if (node)
        free(node);
}

static void apply(tail_node_t *node)
{
    if (node)
        return;
}

Test(linked_tail, tail)
{
    tail_t *tail = malloc(sizeof(*tail));
    tail_node_t *node = malloc(sizeof(*node));

    TAILQ_INIT(tail);
    TAILQ_INSERT_HEAD(tail, node, entries);
    apply_tail(tail, &apply);
    free_tail(tail, &free_node);
}
