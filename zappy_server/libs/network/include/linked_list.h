/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** linked_list
*/

#pragma once

#include <sys/queue.h>
#include <stddef.h>

typedef struct node_s {
    void *data;
    LIST_ENTRY(node_s) entries;
} node_t;

typedef struct tail_node_s {
    void *data;
    TAILQ_ENTRY(tail_node_s) entries;
} tail_node_t;

typedef LIST_HEAD(head_s, node_s) head_t;

typedef TAILQ_HEAD(tail_s, tail_node_s) tail_t;

void apply_list(head_t *head, void (*func)(node_t *node));
void free_list(head_t *head, void(*f_free)(node_t *node));

void apply_tail(tail_t *head, void (*func)(tail_node_t *node));
void free_tail(tail_t *head, void(*f_free)(tail_node_t *node));
