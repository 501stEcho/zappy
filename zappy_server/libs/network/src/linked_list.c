/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** linked_list
*/

#include "linked_list.h"

void apply_list(head_t *head, void (*func)(node_t *node))
{
    node_t *tmp = NULL;

    LIST_FOREACH(tmp, head, entries)
    func(tmp);
    return;
}

void free_list(head_t *head, void (*f_free)(node_t *node))
{
    node_t *tmp = NULL;

    while (!LIST_EMPTY(head)) {
        tmp = LIST_FIRST(head);
        LIST_REMOVE(tmp, entries);
        f_free(tmp);
        tmp = NULL;
    }
    return;
}

void apply_tail(tail_t *tail, void (*func)(tail_node_t *node))
{
    tail_node_t *tmp = NULL;

    TAILQ_FOREACH(tmp, tail, entries)
    func(tmp);
    return;
}

void free_tail(tail_t *tail, void (*f_free)(tail_node_t *node))
{
    tail_node_t *tmp = NULL;

    while (!TAILQ_EMPTY(tail)) {
        tmp = TAILQ_FIRST(tail);
        TAILQ_REMOVE(tail, tmp, entries);
        f_free(tmp);
        tmp = NULL;
    }
    return;
}
