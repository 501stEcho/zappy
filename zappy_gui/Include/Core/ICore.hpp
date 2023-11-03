/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Core.hpp
*/

#pragma once

namespace zappy
{
    class ICore
    {
    public:
        virtual ~ICore() = default;
        virtual auto start(void) -> bool = 0;
    };
}