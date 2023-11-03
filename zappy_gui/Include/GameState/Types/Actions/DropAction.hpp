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
    class DropAction : public Action
    {
    public:
        DropAction(Ressource item)
            : Action(ActionType::DROP), _item(item){};
        virtual ~DropAction() = default;

        auto getItem() -> Ressource { return _item; }

        auto str() const -> std::string override
        {
            std::stringstream ss;
            ss << "drops " << _item;
            return ss.str();
        }
    private:
        Ressource _item;
    };
} // namespace gamestate
