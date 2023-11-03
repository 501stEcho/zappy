/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ConnectAction.hpp
*/

#pragma once

#include "GameState/Types/Action.hpp"
#include "GameState/Types/Drone.hpp"
#include "GameState/Types/Types.hpp"

namespace gamestate
{
    class ConnectAction : public Action
    {
    public:
        ConnectAction(Position position)
            : Action(ActionType::CONNECT), _position(position)
        {
        }
        virtual ~ConnectAction() = default;
        auto getConnectionPosition() const -> Position
        {
            return _position;
        }

        auto str() const -> std::string override
        {
            std::stringstream ss;
            ss << "connected at " << _position;
            return ss.str();
        }

    private:
        Position _position;
    };
} // namespace gamestate