/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** my
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define PERROR(com, value)                                     \
    do {                                                       \
        dprintf(1, "%s:%d '%s' (%s : %s)\n",                     \
        __FILE__, __LINE__, __func__, com, strerror(errno));   \
        return value;                                          \
    } while (0)

#define S_PERROR(com)                                          \
    do {                                                       \
        dprintf(1, "%s:%d '%s' (%s : %s)\n",                     \
        __FILE__, __LINE__, __func__, com, strerror(errno));   \
    } while (0)

#define ERROR(com, value)                       \
    do {                                        \
        dprintf(1, "%s:%d '%s' (%s)\n",         \
        __FILE__, __LINE__, __func__, com);     \
        return value;                           \
    } while (0)

#define S_ERROR(com)                                           \
    do {                                                       \
        dprintf(1, "%s:%d '%s' (%s)\n",                        \
        __FILE__, __LINE__, __func__, com);                    \
    } while (0)

#define MY_FREE(ptr)    \
    do {                \
        if (ptr) {      \
            free(ptr);  \
            ptr = NULL; \
        }               \
    } while (0)

#define F_RETURN(value, func, ...)      \
    do {                                \
        func(__VA_ARGS__);              \
        return value;                   \
    } while (0)
