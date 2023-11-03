/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** MapSizeHandler.hpp
*/

#pragma once

#include "Interpreter/Handler.hpp"
#include <iostream>

namespace interpreter
{
    class MapSizeHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class TileContentHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class ServerFrequencyHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class PlayerConnectionHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class PlayerPositionHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class PlayerDieHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class PlayerBroadcastHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class PlayerExpulsionHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class PlayerForkHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class PlayerDropHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class PlayerCollectHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class IncantationStartHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class IncantationEndHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class PlayerInventoryHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };

    class PlayerLevelHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };
    
    class EndGameHandler : public AHandler
    {
    public:
        void handle(Command &command) override;
    };
}
