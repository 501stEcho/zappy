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
    class ForkAction : public Action
    {
    public:
        ForkAction()
            : Action(ActionType::FORK){};
        virtual ~ForkAction() = default;

        auto str() const -> std::string override
        {
            return "forks";
        }
    };
} // namespace gamestate
