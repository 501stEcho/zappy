/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** GameManager.cpp
*/

#include "GameState/GameManager.hpp"
#include "Beans/Bean.hpp"
#include "GameState/GameState.hpp"
#include "Interpreter/Interpreter.hpp"
#include "Network/Client/Client.hpp"
#include <cstddef>
#include <iostream>

gamestate::GameManager::GameManager()
    : _ioContext(),
      _work(boost::asio::make_work_guard(_ioContext))
{
}

gamestate::GameManager::~GameManager()
{
}

auto gamestate::GameManager::start(void) -> void
{
    std::thread clientThread([this]() {
        _ioContext.run();
    });
    clientThread.detach();
}

auto gamestate::GameManager::stop(void) -> void
{
    _ioContext.post([this]() {
        _work.reset();
        _ioContext.stop();
    });
}

auto gamestate::GameManager::handleMessage(const std::string &message) -> void
{
    _ioContext.post([this, message]() {
        Bean<interpreter::Interpreter>::getInstance().handle(message);
    });
}
