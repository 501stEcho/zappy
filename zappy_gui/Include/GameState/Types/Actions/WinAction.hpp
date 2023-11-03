/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** WinAction.hpp
*/

#pragma once

#include "GameState/Types/Action.hpp"
#include "GameState/Types/Types.hpp"
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

namespace gamestate
{
    class WinAction : public Action
    {
    public:
        WinAction(std::string team)
            : Action(ActionType::WIN), _team(team)
        {
        }
        virtual ~WinAction() = default;

        auto getTeam() -> std::string { return _team; }

        auto str() const -> std::string override
        {
            std::stringstream ss;
            ss << "Victory of the team : " << _team;
            return ss.str();
        }

    private:
        std::string _team;
    };
} // namespace gamestate