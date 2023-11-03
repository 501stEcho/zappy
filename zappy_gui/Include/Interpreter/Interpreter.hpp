/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Interpreter.hpp
*/

#pragma once

#include "AnimationManager/AnimationManager.hpp"
#include "GameState/GameState.hpp"
#include "Interpreter/Handler.hpp"
#include "Interpreter/HandlersImpl.hpp"
#include <cstddef>
#include <functional>
#include <memory>
#include <sstream>
#include <vector>

namespace interpreter
{

    using HandlerConstructor = std::function<std::unique_ptr<IHandler>()>;

    const std::vector<HandlerConstructor> INTERPRETER_HANDLERS = {
    std::make_unique<MapSizeHandler>,
    std::make_unique<TileContentHandler>,
    std::make_unique<ServerFrequencyHandler>,
    std::make_unique<PlayerConnectionHandler>,
    std::make_unique<PlayerPositionHandler>,
    std::make_unique<PlayerDieHandler>,
    std::make_unique<PlayerBroadcastHandler>,
    std::make_unique<PlayerExpulsionHandler>,
    std::make_unique<PlayerForkHandler>,
    std::make_unique<PlayerDropHandler>,
    std::make_unique<PlayerCollectHandler>,
    std::make_unique<PlayerInventoryHandler>,
    std::make_unique<IncantationStartHandler>,
    std::make_unique<IncantationEndHandler>,
    std::make_unique<PlayerLevelHandler>,
    std::make_unique<EndGameHandler>};

    class Interpreter
    {
    public:
        Interpreter()
        {
            std::unique_ptr<IHandler> tmp = nullptr;
            for (auto &handler : INTERPRETER_HANDLERS) {
                tmp = handler();
                if (_handler == nullptr) {
                    _handler = std::move(tmp);
                } else {
                    tmp->setNext(_handler);
                    _handler = std::move(tmp);
                }
            }
        }

        ~Interpreter() = default;

        auto handle(std::string const &command) -> void
        {
            std::stringstream ss(command);
            std::string tmp;
            Command cmd;
            while (ss >> tmp) {
                cmd.args.push_back(tmp);
            }
            cmd.command = cmd.args[0];
            cmd.args.erase(cmd.args.begin());
            cmd.argc = cmd.args.size();

            _handler->handle(cmd);
        }

    private:
        std::unique_ptr<IHandler> _handler;
    };
}