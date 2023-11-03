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
#include <string>

namespace gamestate
{
    class BroadcastAction : public Action
    {
    public:
        BroadcastAction(std::string message)
            : Action(ActionType::BROADCAST), _message(message) {};

        virtual ~BroadcastAction() = default;

        auto getMessage() -> std::string
        {
            return _message;
        }

        auto str() const -> std::string override
        {
            std::stringstream ss;
            ss << "broadcasts \"" << _message << "\"";
            return ss.str();
        }

    private:
        std::string _message;
    };
} // namespace gamestate