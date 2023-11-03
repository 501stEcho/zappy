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
    class TakeAction : public Action
    {
    public:
        TakeAction(Ressource item)
            : Action(ActionType::TAKE), _item(item){};
        virtual ~TakeAction() = default;

        auto getItem() -> Ressource { return _item; }

        auto str() const -> std::string override
        {
            std::stringstream ss;
            ss << "takes " << _item;
            return ss.str();
        }
    private:
        Ressource _item;
    };
} // namespace gamestate
