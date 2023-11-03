/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Bean.hpp
*/

#pragma once

#include <memory>

template <typename T>
class Bean
{
public:
    Bean(const Bean &) = delete;
    Bean &operator=(const Bean &) = delete;

    static T &getInstance()
    {
        static T instance;
        return instance;
    }

    static void destroy()
    {
        getInstance().~T();
    }

protected:
    Bean()
    {
    }
};
