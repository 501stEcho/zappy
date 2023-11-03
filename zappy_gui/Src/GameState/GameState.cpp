/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** GameState.cpp
*/

#include "GameState/GameState.hpp"
#include "GameState/GameManager.hpp"
#include "GameState/Types/Action.hpp"
#include "GameState/Types/Drone.hpp"
#include "GameState/Types/Tile.hpp"
#include "GameState/Types/Types.hpp"
#include <chrono>
#include <cstddef>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

gamestate::GameState::GameState()
    : _mapDimensions{0, 0},
      _map{},
      _frequency{0},
      _winnerSet(false)
{
}

gamestate::GameState::~GameState()
{
}

auto gamestate::GameState::addDrone(std::size_t id, std::size_t x, std::size_t y, Orientation o) -> void
{
    std::lock_guard<std::mutex> lock(_droneMutex);
    TileRef tile = getTile(x, y);
    if (!tile)
        return;
    DroneRef drone = std::make_shared<Drone>(id, tile, o);
    tile->addDrone(drone->getId());
    _drones.insert(_drones.begin(), drone);
}

auto gamestate::GameState::getDrone(std::size_t id) -> DroneRef
{
    std::lock_guard<std::mutex> lock(_droneMutex);
    for (auto &drone : _drones) {
        if (drone->getId() == id)
            return drone;
    }
    return nullptr;
}

auto gamestate::GameState::getDrones() -> std::vector<DroneRef>
{
    std::lock_guard<std::mutex> lock(_droneMutex);
    std::vector<DroneRef> aliveDrones;

    for (DroneRef &drone : _drones) {
        if (drone->isAlive()) {
            aliveDrones.push_back(drone);
        }
    }

    return aliveDrones;
}

auto gamestate::GameState::setMapDimensions(std::size_t width, std::size_t height) -> void
{
    std::lock_guard<std::mutex> lock(_mapMutex);
    _mapDimensions = {width, height};
    _map.clear();
    for (std::size_t y = 0; y < height; ++y) {
        std::vector<TileRef> row;
        for (std::size_t x = 0; x < width; ++x) {
            row.push_back(std::make_shared<Tile>(*this, x, y));
        }
        _map.push_back(row);
    }
}

auto gamestate::GameState::getMapDimensions(void) const -> Dimensions
{
    return _mapDimensions;
}

auto gamestate::GameState::getTile(std::size_t x, std::size_t y) -> TileRef
{
    std::lock_guard<std::mutex> lock(_mapMutex);
    if (x >= _mapDimensions.width || y >= _mapDimensions.height)
        return nullptr;
    return _map[y][x];
}

auto gamestate::GameState::registerAction(std::size_t drone, std::shared_ptr<IAction> &action) -> void
{
    std::lock_guard<std::mutex> lock(_actionMutex);
    DroneRef droneRef = getDrone(drone);
    AssignedAction assignedAction{droneRef, action};
    _lastActions.insert(_lastActions.begin(), assignedAction);
    if (_lastActions.size() > 500)
        _lastActions.pop_back();
}

auto gamestate::GameState::registerAction(std::shared_ptr<IAction> &action) -> void
{
    std::lock_guard<std::mutex> lock(_actionMutex);
    AssignedAction assignedAction{nullptr, action};
    _lastActions.insert(_lastActions.begin(), assignedAction);
    if (_lastActions.size() > 500)
        _lastActions.pop_back();
}

auto gamestate::GameState::getActions() -> std::vector<AssignedAction>
{
    return _lastActions;
}

auto gamestate::GameState::getActions(std::size_t limit) -> std::vector<AssignedAction>
{
    std::lock_guard<std::mutex> lock(_actionMutex);
    std::vector<AssignedAction> actions;

    for (std::size_t i = 0; i < limit && i < _lastActions.size(); ++i)
        actions.push_back(_lastActions[i]);
    return actions;
}

auto gamestate::GameState::getFrequency() const -> std::size_t
{
    return _frequency;
}

auto gamestate::GameState::setFrequency(std::size_t frequency) -> void
{
    _frequency = frequency;
}

auto gamestate::GameState::getWinner() const -> std::string
{
    return _winner;
}

auto gamestate::GameState::setWinner(std::string winner) -> void
{
    _winner = winner;
    _winnerSet = true;
}

auto gamestate::GameState::isWinnerSet() const -> bool
{
    return _winnerSet;
}

auto gamestate::GameState::getDeathCount() -> std::size_t
{
    std::lock_guard<std::mutex> lock(_droneMutex);
    std::size_t deathCount = 0;
    for (DroneRef &drone : _drones) {
        if (!drone->isAlive())
            deathCount++;
    }
    return deathCount;
}
