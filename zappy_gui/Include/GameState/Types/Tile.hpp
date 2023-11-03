/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Drone.hpp
*/

#pragma once

#include "GameState/GameState.hpp"
#include "GameState/Types/Types.hpp"
#include <cstddef>
#include <map>
#include <memory>
#include <vector>

namespace gamestate
{

    class GameState;
    class Drone;
    using DroneRef = std::shared_ptr<Drone>;

    class Tile
    {
    public:
        Tile(GameState &gameState, std::size_t x, std::size_t y)
            : _gameState(gameState), _coordinates({x, y})
        {
            for (std::size_t i = 0; i < 7; ++i)
                _ressources.insert({static_cast<Ressource>(i), 0});
        }

        auto addDrone(std::size_t _id) -> void;
        auto removeDrone(std::size_t id) -> void;
        auto getDrones() -> std::vector<DroneRef>;
        auto setRessource(Ressource ressource, std::size_t amount) -> void;
        auto getPosition() const -> Coordinates;
        auto getRessource(Ressource) const -> std::size_t;

    private:
        GameState &_gameState;
        Coordinates _coordinates;
        std::map<Ressource, std::size_t> _ressources;
        std::vector<std::size_t> _drones;
    };
}