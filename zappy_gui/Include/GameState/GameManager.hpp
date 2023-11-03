/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** GameManager.hpp
*/

#pragma once

#include "AnimationManager/AnimationManager.hpp"
#include "GameState/GameState.hpp"
#include "Interpreter/Interpreter.hpp"
#include "Network/Client/Client.hpp"
#include <boost/asio.hpp>

namespace network {
    class Client;
}

namespace gamestate
{
    class GameManager
    {
    public:
        GameManager();
        ~GameManager();

        auto start(void) -> void;
        auto stop(void) -> void;
        auto handleMessage(const std::string &message) -> void;

    private:
        boost::asio::io_context _ioContext;
        boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _work;
    };
}
