/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Drone.cpp
*/

#include "GameState/Types/Drone.hpp"
#include "GameState/Types/Tile.hpp"
#include "GameState/Types/Types.hpp"
#include <string>

gamestate::DroneState::DroneState(Position position) : _position(position)
{
    _animationType = animation::Type::IDLE;
    _animationFrame = 0;
}

void gamestate::DroneHandler::addDrone(unsigned int index, Position position)
{
    if (droneExist(index))
        throw DroneException("Drone already existing");
    _drones.insert({index, DroneState(position)});
}

bool gamestate::DroneHandler::droneExist(unsigned int index)
{
    return (_drones.find(index) != _drones.end());
}

gamestate::DroneState &gamestate::DroneHandler::getDrone(unsigned int index)
{
    if (_drones.find(index) != _drones.end())
        return _drones.at(index);
    else
        throw DroneException(std::to_string(index) + " Drone index not found");
}

auto gamestate::Drone::getId(void) const -> std::size_t
{
    return _id;
}

auto gamestate::Drone::getPosition(void) const -> Position
{
    return _position;
}

auto gamestate::Drone::setPosition(TileRef tile, Orientation o) -> void
{
    _position.tile->removeDrone(_id);
    _position = {tile, o};
    tile->addDrone(_id);
}

auto gamestate::Drone::kill(void) -> void
{
    _isAlive = false;
}

auto gamestate::Drone::isAlive(void) const -> bool
{
    return _isAlive;
}

auto gamestate::Drone::setRessource(Ressource ressource, std::size_t amount) -> void
{
    _inventory[ressource] = amount;
}

auto gamestate::Drone::getRessource(Ressource ressource) const -> std::size_t
{
    return _inventory.at(ressource);
}

auto gamestate::Drone::setLevel(std::size_t level) -> void
{
    _level = level;
}

auto gamestate::Drone::getLevel(void) const -> std::size_t
{
    return _level;
}

auto gamestate::Drone::setTeam(std::string team) -> void
{
    _team = team;
}

auto gamestate::Drone::getTeam(void) const -> std::string
{
    return _team;
}

std::ostream &operator<<(std::ostream &os, gamestate::Position const &position)
{
    gamestate::Coordinates tilePos = position.tile->getPosition();
    return os << "{x: " << tilePos.x << ", y: " << tilePos.y << ", o: " << position.orientation << "}";
}