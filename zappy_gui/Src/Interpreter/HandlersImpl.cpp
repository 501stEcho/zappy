/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** MapSizeHandler.cpp
*/

#include "Interpreter/HandlersImpl.hpp"
#include "AnimationManager/Animations/BroadcastAnimation.hpp"
#include "AnimationManager/Animations/IncantationEndAnimation.hpp"
#include "AnimationManager/Animations/IncantationStartAnimation.hpp"
#include "GameState/GameManager.hpp"
#include "GameState/Types/Actions/BroadcastAction.hpp"
#include "GameState/Types/Actions/ConnectAction.hpp"
#include "GameState/Types/Actions/DieAction.hpp"
#include "GameState/Types/Actions/DropAction.hpp"
#include "GameState/Types/Actions/ExpulseAction.hpp"
#include "GameState/Types/Actions/ForkAction.hpp"
#include "GameState/Types/Actions/IncantationEndAction.hpp"
#include "GameState/Types/Actions/IncatationAction.hpp"
#include "GameState/Types/Actions/LevelAction.hpp"
#include "GameState/Types/Actions/MoveAction.hpp"
#include "GameState/Types/Actions/TakeAction.hpp"
#include "GameState/Types/Actions/WinAction.hpp"
#include "GameState/Types/Drone.hpp"
#include "GameState/Types/Tile.hpp"
#include "GameState/Types/Types.hpp"
#include "Interpreter/Handler.hpp"
#include <cstddef>
#include <memory>
#include <sstream>
#include <string>

void interpreter::MapSizeHandler::handle(Command &command)
{
    if (command.command != "msz" || command.argc != 2)
        return AHandler::handle(command);
    std::size_t width = std::stoul(command.args[0]);
    std::size_t height = std::stoul(command.args[1]);
    Bean<gamestate::GameState>::getInstance().setMapDimensions(width, height);
}

void interpreter::TileContentHandler::handle(Command &command)
{
    if (command.command != "bct" || command.argc != 9)
        return AHandler::handle(command);
    std::size_t x = std::stoul(command.args[0]);
    std::size_t y = std::stoul(command.args[1]);
    std::size_t food = std::stoul(command.args[2]);
    std::size_t linemate = std::stoul(command.args[3]);
    std::size_t deraumere = std::stoul(command.args[4]);
    std::size_t sibur = std::stoul(command.args[5]);
    std::size_t mendiane = std::stoul(command.args[6]);
    std::size_t phiras = std::stoul(command.args[7]);
    std::size_t thystame = std::stoul(command.args[8]);

    auto &gameState = Bean<gamestate::GameState>::getInstance();

    gameState.getTile(x, y)->setRessource(gamestate::FOOD, food);
    gameState.getTile(x, y)->setRessource(gamestate::LINEMATE, linemate);
    gameState.getTile(x, y)->setRessource(gamestate::DERAUMERE, deraumere);
    gameState.getTile(x, y)->setRessource(gamestate::SIBUR, sibur);
    gameState.getTile(x, y)->setRessource(gamestate::MENDIANE, mendiane);
    gameState.getTile(x, y)->setRessource(gamestate::PHIRAS, phiras);
    gameState.getTile(x, y)->setRessource(gamestate::THYSTAME, thystame);
}

void interpreter::ServerFrequencyHandler::handle(Command &command)
{
    if (command.command != "sgt" || command.argc != 1)
        return AHandler::handle(command);
    std::size_t frequency = std::stoul(command.args[0]);
    Bean<gamestate::GameState>::getInstance().setFrequency(frequency);
}

void interpreter::PlayerConnectionHandler::handle(Command &command)
{
    if (command.command != "pnw" || command.argc != 6)
        return AHandler::handle(command);
    std::size_t id = std::stoul(command.args[0]);
    std::size_t x = std::stoul(command.args[1]);
    std::size_t y = std::stoul(command.args[2]);

    gamestate::Orientation orientation = static_cast<gamestate::Orientation>(std::stoul(command.args[3]));

    std::size_t level = std::stoul(command.args[4]);
    std::string teamName = command.args[5];

    auto &gameState = Bean<gamestate::GameState>::getInstance();
    gameState.addDrone(id, x, y, orientation);
    auto drone = gameState.getDrone(id);
    drone->setLevel(level);
    drone->setTeam(teamName);

    auto tile = gameState.getTile(x, y);
    std::shared_ptr<gamestate::IAction> action = std::make_shared<gamestate::ConnectAction>(gamestate::Position{tile, orientation});
    gameState.registerAction(id, action);
}

void interpreter::PlayerPositionHandler::handle(Command &command)
{
    if (command.command != "ppo" || command.argc != 4)
        return AHandler::handle(command);
    std::size_t id = std::stoul(command.args[0]);
    std::size_t x = std::stoul(command.args[1]);
    std::size_t y = std::stoul(command.args[2]);

    auto &gameState = Bean<gamestate::GameState>::getInstance();

    auto drone = gameState.getDrone(id);
    auto oldPosition = drone->getPosition();

    gamestate::Orientation orientation = static_cast<gamestate::Orientation>(std::stoul(command.args[3]));
    gamestate::TileRef destination = gameState.getTile(x, y);
    drone->setPosition(destination, orientation);

    std::shared_ptr<gamestate::IAction> action = std::make_shared<gamestate::MoveAction>(oldPosition, gamestate::Position{destination, orientation});
    gameState.registerAction(id, action);
}

void interpreter::PlayerDieHandler::handle(Command &command)
{
    if (command.command != "pdi" || command.argc != 1)
        return AHandler::handle(command);
    std::size_t id = std::stoul(command.args[0]);

    auto &gameState = Bean<gamestate::GameState>::getInstance();

    gameState.getDrone(id)->kill();

    std::shared_ptr<gamestate::IAction> action = std::make_shared<gamestate::DieAction>();
    gameState.registerAction(id, action);
}

void interpreter::PlayerBroadcastHandler::handle(Command &command)
{
    if (command.command != "pbc" || command.argc != 2)
        return AHandler::handle(command);
    std::size_t id = std::stoul(command.args[0]);
    std::string message = command.args[1];

    auto &gameState = Bean<gamestate::GameState>::getInstance();
    auto &animationManager = Bean<animation::AnimationManager>::getInstance();

    std::shared_ptr<gamestate::IAction> action = std::make_shared<gamestate::BroadcastAction>(message);
    gameState.registerAction(id, action);

    std::unique_ptr<animation::Animation> animation = std::make_unique<animation::BroadcastAnimation>(gameState.getDrone(id)->getPosition().tile, message);
    animationManager.playAnimation(std::move(animation));
}

void interpreter::PlayerExpulsionHandler::handle(Command &command)
{
    if (command.command != "pex" || command.argc != 1)
        return AHandler::handle(command);
    std::size_t id = std::stoul(command.args[0]);

    auto &gameState = Bean<gamestate::GameState>::getInstance();

    std::shared_ptr<gamestate::IAction> action = std::make_shared<gamestate::ExpulseAction>();
    gameState.registerAction(id, action);
}

void interpreter::PlayerForkHandler::handle(Command &command)
{
    if (command.command != "pfk" || command.argc != 1)
        return AHandler::handle(command);
    std::size_t id = std::stoul(command.args[0]);

    auto &gameState = Bean<gamestate::GameState>::getInstance();

    std::shared_ptr<gamestate::IAction> action = std::make_shared<gamestate::ForkAction>();
    gameState.registerAction(id, action);
}

void interpreter::PlayerDropHandler::handle(Command &command)
{
    if (command.command != "pdr" || command.argc != 2)
        return AHandler::handle(command);
    std::size_t id = std::stoul(command.args[0]);
    gamestate::Ressource resource = static_cast<gamestate::Ressource>(std::stoul(command.args[1]));

    auto &gameState = Bean<gamestate::GameState>::getInstance();

    std::shared_ptr<gamestate::IAction> action = std::make_shared<gamestate::DropAction>(resource);
    gameState.registerAction(id, action);
}

void interpreter::PlayerCollectHandler::handle(Command &command)
{
    if (command.command != "pgt" || command.argc != 2)
        return AHandler::handle(command);
    std::size_t id = std::stoul(command.args[0]);
    gamestate::Ressource resource = static_cast<gamestate::Ressource>(std::stoul(command.args[1]));

    auto &gameState = Bean<gamestate::GameState>::getInstance();

    std::shared_ptr<gamestate::IAction> action = std::make_shared<gamestate::TakeAction>(resource);
    gameState.registerAction(id, action);
}

void interpreter::PlayerInventoryHandler::handle(Command &command)
{
    if (command.command != "pin" || command.argc != 10)
        return AHandler::handle(command);
    std::size_t id = std::stoul(command.args[0]);
    std::size_t food = std::stoul(command.args[3]);
    std::size_t linemate = std::stoul(command.args[4]);
    std::size_t deraumere = std::stoul(command.args[5]);
    std::size_t sibur = std::stoul(command.args[6]);
    std::size_t mendiane = std::stoul(command.args[7]);
    std::size_t phiras = std::stoul(command.args[8]);
    std::size_t thystame = std::stoul(command.args[9]);

    auto &gameState = Bean<gamestate::GameState>::getInstance();

    gameState.getDrone(id)->setRessource(gamestate::FOOD, food);
    gameState.getDrone(id)->setRessource(gamestate::LINEMATE, linemate);
    gameState.getDrone(id)->setRessource(gamestate::DERAUMERE, deraumere);
    gameState.getDrone(id)->setRessource(gamestate::SIBUR, sibur);
    gameState.getDrone(id)->setRessource(gamestate::MENDIANE, mendiane);
    gameState.getDrone(id)->setRessource(gamestate::PHIRAS, phiras);
    gameState.getDrone(id)->setRessource(gamestate::THYSTAME, thystame);
}

void interpreter::IncantationStartHandler::handle(Command &command)
{
    if (command.command != "pic" || command.argc < 4)
        return AHandler::handle(command);
    std::size_t x = std::stoul(command.args[0]);
    std::size_t y = std::stoul(command.args[1]);
    std::size_t level = std::stoul(command.args[2]);
    std::size_t incantor = std::stoul(command.args[3]);

    std::vector<gamestate::DroneRef> ids;

    for (std::size_t i = 3; i < command.argc; i++) {
        std::size_t id = std::stoul(command.args[i]);
        ids.push_back(Bean<gamestate::GameState>::getInstance().getDrone(id));
    }

    auto &gameState = Bean<gamestate::GameState>::getInstance();
    auto &animationManager = Bean<animation::AnimationManager>::getInstance();
    auto tile = gameState.getTile(x, y);

    std::shared_ptr<gamestate::IAction> action = std::make_shared<gamestate::IncantataionAction>(tile, level, ids);
    gameState.registerAction(incantor, action);

    std::unique_ptr<animation::Animation> animation = std::make_unique<animation::IncantationStartAnimation>(tile);
    animationManager.playAnimation(std::move(animation));
}

void interpreter::IncantationEndHandler::handle(Command &command)
{
    if (command.command != "pie" || command.argc != 3)
        return AHandler::handle(command);
    std::size_t x = std::stoul(command.args[0]);
    std::size_t y = std::stoul(command.args[1]);

    auto &gameState = Bean<gamestate::GameState>::getInstance();
    auto &animationManager = Bean<animation::AnimationManager>::getInstance();
    auto tile = gameState.getTile(x, y);

    std::shared_ptr<gamestate::IAction> action = std::make_shared<gamestate::IncantationEndAction>(tile);
    gameState.registerAction(action);

    std::unique_ptr<animation::Animation> animation = std::make_unique<animation::IncantationEndAnimation>(tile);
    animationManager.playAnimation(std::move(animation));
}

void interpreter::PlayerLevelHandler::handle(Command &command)
{
    if (command.command != "plv" || command.argc != 2)
        return AHandler::handle(command);
    std::size_t id = std::stoi(command.args[0]);
    std::size_t level = std::stoi(command.args[1]);

    auto &gameState = Bean<gamestate::GameState>::getInstance();
    gameState.getDrone(id)->setLevel(level);

    std::shared_ptr<gamestate::IAction> action = std::make_shared<gamestate::LevelAction>(level);
    gameState.registerAction(action);
}

void interpreter::EndGameHandler::handle(Command &command)
{
    if (command.command != "seg" || command.argc != 1)
        return AHandler::handle(command);
    std::string winner = command.args[0];

    auto &gameState = Bean<gamestate::GameState>::getInstance();
    gameState.setWinner(winner);

    std::shared_ptr<gamestate::IAction> action = std::make_shared<gamestate::WinAction>(winner);
    gameState.registerAction(action);
}