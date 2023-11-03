/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Tile.cpp
*/

#include "GameState/Types/Tile.hpp"
#include "GameState/GameState.hpp"
#include "GameState/Types/Drone.hpp"
#include "GameState/Types/Types.hpp"
#include <cstddef>
#include <vector>

auto gamestate::Tile::addDrone(std::size_t _id) -> void
{
    _drones.push_back(_id);
}

auto gamestate::Tile::removeDrone(std::size_t id) -> void
{
    for (auto it = _drones.begin(); it != _drones.end(); ++it) {
        if (*it == id) {
            _drones.erase(it);
            return;
        }
    }
}

auto gamestate::Tile::getDrones() -> std::vector<DroneRef>
{
    std::vector<DroneRef> drones;

    for (auto &id : _drones) {
        DroneRef drone = _gameState.getDrone(id);
        if (!drone || !drone->isAlive())
            continue;
        drones.push_back(drone);
    }

    return drones;
}

auto gamestate::Tile::setRessource(Ressource ressource, std::size_t amount) -> void
{
    _ressources[ressource] = amount;
}

auto gamestate::Tile::getPosition() const -> Coordinates
{
    return _coordinates;
}

std::ostream &operator<<(std::ostream &os, const gamestate::TileRef &position)
{
    gamestate::Coordinates pos = position->getPosition();
    return os << "{x: " << pos.x << ", y: " << pos.y << "}";
}

auto gamestate::Tile::getRessource(Ressource ressource) const -> std::size_t
{
    return _ressources.at(ressource);
}
