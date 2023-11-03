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
    class IncantataionAction : public Action
    {
    public:
        IncantataionAction(TileRef tile, std::size_t level, std::vector<DroneRef> players)
            : Action(ActionType::INCANTATION), _tile(tile), _level(level), _players(players)
        {
        }
        virtual ~IncantataionAction() = default;


        auto getTile() -> TileRef { return _tile; }
        auto getLevel() -> std::size_t { return _level; }
        auto getAffected() -> std::vector<DroneRef> { return _players; }

        auto str() const -> std::string override
        {
            std::stringstream ss;
            ss << "starts incantation at " << _tile;
            return ss.str();
        }

    private:
        TileRef _tile;
        std::size_t _level;
        std::vector<DroneRef> _players;
    };
} // namespace gamestate