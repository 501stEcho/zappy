/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ConnectAction.hpp
*/

#pragma once

#include "GameState/Types/Action.hpp"
#include "GameState/Types/Types.hpp"

namespace gamestate
{
    class ExpulseAction : public Action
    {
    public:
        ExpulseAction()
            : Action(ActionType::EXPULSE){};
        virtual ~ExpulseAction() = default;

        auto str() const -> std::string override
        {
            return "expulses";
        }
    };
} // namespace gamestate
