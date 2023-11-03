/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ConnectAction.hpp
*/

#pragma once

#include "GameState/Types/Action.hpp"
#include "GameState/Types/Types.hpp"
#include <cstddef>
#include <sstream>
#include <vector>

namespace gamestate
{
    class LevelAction : public Action
    {
    public:
        LevelAction(std::size_t level)
            : Action(ActionType::LEVEL), _level(level)
        {
        }
        virtual ~LevelAction() = default;

        auto getLevel() -> std::size_t { return _level; }

        auto str() const -> std::string override
        {
            std::stringstream ss;
            ss << "leveled up to level " << _level;
            return ss.str();
        }

    private:
        std::size_t _level;
    };
} // namespace gamestate