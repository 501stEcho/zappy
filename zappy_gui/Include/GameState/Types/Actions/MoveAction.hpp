/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ConnectAction.hpp
*/

#pragma once

#include "GameState/Types/Action.hpp"
#include "GameState/Types/Types.hpp"
#include <sstream>

namespace gamestate
{
    class MoveAction : public Action
    {
    public:
        MoveAction(Position from, Position to)
            : Action(ActionType::MOVE), _from(from), _to(to)
        {
        }
        virtual ~MoveAction() = default;

        auto getOldPosition() const -> Position
        {
            return _from;
        }

        auto getNewPosition() const -> Position
        {
            return _to;
        }

        auto str() const -> std::string override
        {
            std::stringstream ss;
            ss << "moved to " << _to;
            return ss.str();
        }

    private:
        Position _from;
        Position _to;
    };
} // namespace gamestate