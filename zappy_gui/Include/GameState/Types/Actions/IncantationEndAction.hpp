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
    class IncantationEndAction : public Action
    {
    public:
        IncantationEndAction(TileRef tile)
            : Action(ActionType::END_INCANTATION), _tile(tile)
        {
        }
        virtual ~IncantationEndAction() = default;


        auto getTile() -> TileRef { return _tile; }

        auto str() const -> std::string override
        {
            std::stringstream ss;
            ss << "incantation at " << _tile << " ended";
            return ss.str();
        }

    private:
        TileRef _tile;
    };
} // namespace gamestate