/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Drone.hpp
*/

#pragma once

#include "GameState/Types/Drone.hpp"
#include "GameState/Types/Types.hpp"
#include <chrono>
#include <cstddef>
#include <memory>
#include <ratio>

namespace gamestate
{

    class IAction
    {
    public:
        virtual ~IAction() = default;
        virtual auto getElapsedTime() const -> std::chrono::duration<long, std::ratio<1, 1000>> = 0;
        virtual auto getActionType() const -> ActionType = 0;
        virtual auto str() const -> std::string = 0;
    };

    class Action : public IAction
    {
    public:
        Action(ActionType type)
            : _startTime(std::chrono::system_clock::now()), _type(type)
        {
        }
        virtual ~Action() = default;

        auto getElapsedTime() const -> std::chrono::duration<long, std::ratio<1, 1000>> override
        {
            auto now = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _startTime);
            return elapsed;
        }

        auto getActionType() const -> ActionType override
        {
            return _type;
        }

        virtual auto str() const -> std::string override = 0;

    private:
        std::chrono::time_point<std::chrono::system_clock> _startTime;
        ActionType _type;
    };
}