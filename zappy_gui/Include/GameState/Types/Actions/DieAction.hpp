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
    class DieAction : public Action
    {
    public:
        DieAction()
            : Action(ActionType::DIE){};
        virtual ~DieAction() = default;

        auto str() const -> std::string override
        {
            return "died";
        }
    };
} // namespace gamestate
