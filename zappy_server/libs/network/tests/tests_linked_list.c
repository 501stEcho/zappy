/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** tests_linked_list
*/

#include <criterion/criterion.h>

#include "linked_list.h"

static void free_node(node_t *node)
{
    if (node)
        free(node);
}

static void apply(node_t *node)
{
    if (node)
        return;
}

Test(linked_list, list)
{
    head_t *list = malloc(sizeof(*list));
    node_t *node = malloc(sizeof(*node));

    LIST_INIT(list);
    LIST_INSERT_HEAD(list, node, entries);
    apply_list(list, &apply);
    free_list(list, &free_node);
}
