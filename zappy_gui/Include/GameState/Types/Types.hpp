/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** GameManager.hpp
*/

#pragma once

#include <boost/asio.hpp>
#include <cstddef>
#include <ostream>

namespace gamestate
{
    struct Coordinates {
        std::size_t x;
        std::size_t y;
        bool operator<(const Coordinates &other) const
        {
            if (y == other.y)
                return (x < other.x);
            else
                return (y < other.y);
        }
    };

    struct Dimensions {
        std::size_t width;
        std::size_t height;
    };

    enum Orientation {
        NORTH = 1,
        EAST,
        SOUTH,
        WEST
    };

    enum Ressource {
        FOOD = 0,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    };

    enum ActionType {
        CONNECT,
        MOVE,
        EXPULSE,
        BROADCAST,
        INCANTATION,
        END_INCANTATION,
        FORK,
        DROP,
        TAKE,
        DIE,
        LEVEL,
        WIN
    };

    namespace AnimationType {
        enum Type  {
            IDLE,
            MOVE,
            BROADCAST,
            INCANTATION,
            FORK,
            DIE,
            TALE,
            DROP
        };
    }

    class Tile;

    using TileRef = std::shared_ptr<Tile>;
    using Map = std::vector<std::vector<TileRef>>;

    class Drone;

    using DroneRef = std::shared_ptr<Drone>;
}

std::ostream &operator<<(std::ostream &os, const gamestate::TileRef &position);

inline std::ostream &operator<<(std::ostream &os, gamestate::Orientation const &orientation)
{
    if (orientation == gamestate::NORTH)
        return os << "NORTH";
    if (orientation == gamestate::EAST)
        return os << "EAST";
    if (orientation == gamestate::SOUTH)
        return os << "SOUTH";
    if (orientation == gamestate::WEST)
        return os << "WEST";
    return os;
}

inline std::ostream &operator<<(std::ostream &os, gamestate::Ressource const &ressource)
{
    if (ressource == gamestate::FOOD)
        return os << "FOOD";
    if (ressource == gamestate::LINEMATE)
        return os << "LINEMATE";
    if (ressource == gamestate::DERAUMERE)
        return os << "DERAUMERE";
    if (ressource == gamestate::SIBUR)
        return os << "SIBUR";
    if (ressource == gamestate::MENDIANE)
        return os << "MENDIANE";
    if (ressource == gamestate::PHIRAS)
        return os << "PHIRAS";
    if (ressource == gamestate::THYSTAME)
        return os << "THYSTAME";
    return os;
}


 namespace animation {
        enum Type  {
            IDLE,
            MOVE,
            BROADCAST,
            INCANTATION,
            INCANTATION_END,
            FORK,
            DIE,
            TALE,
            DROP
        };
    }