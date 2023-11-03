/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Drone.hpp
*/

#pragma once

#include "GameState/Types/Types.hpp"
#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <string>

namespace gamestate
{

    class Tile;
    using TileRef = std::shared_ptr<Tile>;

    struct Position {
        TileRef tile;
        Orientation orientation;
    };

    class DroneException : public std::exception {
        public:
            DroneException(std::string reason) : _reason(reason) {};
            const char *what() const noexcept override
            {
                return _reason.c_str();
            }
        private:
            std::string _reason;
    };

    struct DroneState {
        DroneState(Position position);
        Position _position;
        unsigned int _animationFrame;
        animation::Type _animationType;
    };

    class DroneHandler {
        public:
            void addDrone(unsigned int index, Position position);
            bool droneExist(unsigned int index);
            DroneState &getDrone(unsigned int index);
        private:
            std::map<unsigned int, DroneState> _drones;
    };

    class Drone
    {
    public:
        Drone()
            : _id(0), _level(1), _position({nullptr, Orientation::NORTH}), _isAlive(true)
        {
            for (std::size_t i = 0; i < 7; ++i)
                _inventory.insert({static_cast<Ressource>(i), i == 0 ? 9 : 0});
        }
        Drone(std::size_t id, TileRef tile, Orientation orientation)
            : _id(id), _level(1), _position({tile, orientation}), _isAlive(true)
        {
            for (std::size_t i = 0; i < 7; ++i)
                _inventory.insert({static_cast<Ressource>(i), i == 0 ? 9 : 0});
        }
        ~Drone() {}

        auto getId(void) const -> std::size_t;
        auto getPosition(void) const -> Position;
        auto setPosition(TileRef tile, Orientation o) -> void;
        auto kill(void) -> void;
        auto isAlive(void) const -> bool;
        auto setRessource(Ressource ressource, std::size_t amount) -> void;
        auto getRessource(Ressource) const -> std::size_t;
        auto setLevel(std::size_t level) -> void;
        auto getLevel(void) const -> std::size_t;
        auto setTeam(std::string team) -> void;
        auto getTeam(void) const -> std::string;

    private:
        std::size_t _id;
        std::size_t _level;
        Position _position;
        bool _isAlive;
        std::map<Ressource, std::size_t> _inventory;
        std::string _team;
    };

}

std::ostream &operator<<(std::ostream &os, gamestate::Position const &position);