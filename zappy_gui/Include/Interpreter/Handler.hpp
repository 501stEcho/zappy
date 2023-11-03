/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** Client
*/

#pragma once

#include "AnimationManager/AnimationManager.hpp"
#include "GameState/GameState.hpp"
#include <memory>
#include <vector>
#include <string>

class UserInterface;

namespace interpreter
{
    struct Command {
        std::string command;
        std::vector<std::string> args;
        std::size_t argc;
    };

    class IHandler
    {
    public:
        virtual ~IHandler() = default;
        virtual void setNext(std::unique_ptr<IHandler> &handler) = 0;
        virtual void handle(Command &command) = 0;
    };

    class AHandler : public IHandler
    {
    private:
        std::unique_ptr<IHandler> next_handler_;

    public:
        AHandler()
            : next_handler_(nullptr)
        {
        }

        void setNext(std::unique_ptr<IHandler> &handler) override
        {
            this->next_handler_ = std::move(handler);
        }

        void handle(Command &command) override
        {
            if (this->next_handler_) {
                return this->next_handler_->handle(command);
            }
        }
    };
}
