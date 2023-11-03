/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** GameManager.hpp
*/

#pragma once

#include "GameState/Types/Action.hpp"
#include "GameState/Types/Drone.hpp"
#include "GameState/Types/Tile.hpp"
#include "GameState/Types/Types.hpp"
#include <boost/asio.hpp>
#include <chrono>
#include <cstddef>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace gamestate
{
    struct AssignedAction {
        DroneRef drone;
        std::shared_ptr<IAction> action;
    };

    class GameState
    {
    public:
        GameState();
        ~GameState();

        auto addDrone(std::size_t id, std::size_t x, std::size_t y, Orientation o) -> void;
        auto getDrone(std::size_t id) -> DroneRef;
        auto getDrones() -> std::vector<DroneRef>;

        auto setMapDimensions(std::size_t width, std::size_t height) -> void;
        auto getMapDimensions(void) const -> Dimensions;

        auto registerAction(std::size_t drone, std::shared_ptr<IAction> &action) -> void;
        auto registerAction(std::shared_ptr<IAction> &action) -> void;

        auto getActions() -> std::vector<AssignedAction>;
        auto getActions(std::size_t limit) -> std::vector<AssignedAction>;

        auto getDeathCount() -> std::size_t;

        auto getTile(std::size_t x, std::size_t y) -> TileRef;

        auto getFrequency() const -> std::size_t;
        auto setFrequency(std::size_t frequency) -> void;

        auto isWinnerSet() const -> bool;
        auto getWinner() const -> std::string;
        auto setWinner(std::string team) -> void;

    private:
        Dimensions _mapDimensions;
        Map _map;
        std::mutex _droneMutex;
        std::mutex _mapMutex;
        std::mutex _actionMutex;
        std::vector<DroneRef> _drones;
        std::vector<AssignedAction> _lastActions;
        std::string _winner;
        std::size_t _frequency;
        bool _winnerSet;
    };
}
