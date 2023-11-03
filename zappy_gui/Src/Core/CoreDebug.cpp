/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** CoreDebug.cpp
*/

#include "Core/CoreDebug.hpp"
#include "AnimationManager/AnimationManager.hpp"
#include "GameState/GameState.hpp"
#include "GameState/Types/Types.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <sstream>

zappy::CoreDebug::CoreDebug()
    : _window(sf::VideoMode(1900, 800), "Zappy")
{
    _font = sf::Font();
    _font.loadFromFile("Sources/font/font.ttf");
    _window.setFramerateLimit(60);
}

zappy::CoreDebug::~CoreDebug()
{
}

void drawGrid(sf::RenderWindow &window, gamestate::GameState &gameState)
{
    auto mapDims = gameState.getMapDimensions();

    double width = (double)window.getSize().y / mapDims.height;
    sf::RectangleShape rectangle(sf::Vector2f(width, width));
    rectangle.setFillColor(sf::Color(255, 255, 255));
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(sf::Color(0, 0, 0));

    for (std::size_t i = 0; i < mapDims.width; i++) {
        for (std::size_t j = 0; j < mapDims.height; j++) {
            rectangle.setPosition(i * width, j * width);
            window.draw(rectangle);
        }
    }
}

void showDroneCount(
sf::RenderWindow &window, gamestate::GameState &gameState, sf::Font &font)
{
    auto drones = gameState.getDrones();
    auto mapDims = gameState.getMapDimensions();
    double width = (double)window.getSize().y / mapDims.height;

    for (std::size_t i = 0; i < mapDims.width; i++) {
        for (std::size_t j = 0; j < mapDims.height; j++) {
            std::size_t count = 0;
            for (auto &drone : drones) {
                auto pos = drone->getPosition().tile->getPosition();
                if (pos.x == i && pos.y == j)
                    count++;
            }
            if (count == 0)
                continue;
            sf::Text text(std::to_string(count), font, width / 4);
            text.setFillColor(sf::Color(0, 0, 0));
            text.setPosition(i * width + width * 0.75, j * width);
            window.draw(text);
        }
    }
}

void showFoodCount(
sf::RenderWindow &window, gamestate::GameState &gameState, sf::Font &font)
{
    auto mapDims = gameState.getMapDimensions();
    double width = (double)window.getSize().y / mapDims.height;

    std::map<gamestate::Ressource, sf::Color> colors = {
    {gamestate::Ressource::FOOD, sf::Color(130, 0, 0)},
    {gamestate::Ressource::LINEMATE, sf::Color(0, 130, 0)},
    {gamestate::Ressource::DERAUMERE, sf::Color(0, 0, 130)},
    {gamestate::Ressource::SIBUR, sf::Color(130, 130, 0)},
    {gamestate::Ressource::MENDIANE, sf::Color(0, 130, 130)},
    {gamestate::Ressource::PHIRAS, sf::Color(130, 0, 130)},
    {gamestate::Ressource::THYSTAME, sf::Color(85, 0, 130)},
    };

    std::map<gamestate::Ressource, std::size_t> counts = {
    {gamestate::Ressource::FOOD, 0}, {gamestate::Ressource::LINEMATE, 0},
    {gamestate::Ressource::DERAUMERE, 0}, {gamestate::Ressource::SIBUR, 0},
    {gamestate::Ressource::MENDIANE, 0}, {gamestate::Ressource::PHIRAS, 0},
    {gamestate::Ressource::THYSTAME, 0}};

    for (std::size_t i = 0; i < mapDims.width; i++) {
        for (std::size_t j = 0; j < mapDims.height; j++) {
            std::size_t yGap = 0;
            for (auto &ressource : colors) {
                std::size_t count =
                gameState.getTile(i, j)->getRessource(ressource.first);
                sf::Text text(std::to_string(count), font, width / 7);
                text.setFillColor(ressource.second);
                text.setPosition(i * width, j * width + yGap);
                window.draw(text);
                yGap += width / 7;
                counts[ressource.first] += count;
            }
        }
    }

    std::size_t yGap = 0;
    for (auto &ressource : colors) {
        std::stringstream ss;
        ss << ressource.first << ": " << counts[ressource.first];
        sf::Text text(ss.str(), font, 20);
        text.setFillColor(ressource.second);
        text.setPosition(mapDims.width * width + 500, yGap);
        window.draw(text);
        yGap += 20;
    }
}

sf::Color idToColor(std::size_t id)
{
    sf::Color colors[] = {
    sf::Color(255, 0, 0),
    sf::Color(0, 255, 0),
    sf::Color(0, 0, 255),
    sf::Color(255, 255, 0),
    sf::Color(0, 255, 255),
    sf::Color(255, 0, 255),
    sf::Color(192, 192, 192),
    sf::Color(128, 128, 128),
    sf::Color(128, 0, 0),
    sf::Color(128, 128, 0),
    sf::Color(0, 128, 0),
    sf::Color(128, 0, 128),
    sf::Color(0, 128, 128),
    sf::Color(0, 0, 128),
    };
    return colors[id % 14];
}

void drawDrone(sf::RenderWindow &window, gamestate::GameState &gameState)
{
    auto mapDims = gameState.getMapDimensions();
    auto drones = gameState.getDrones();

    double width = (double)window.getSize().y / mapDims.height;
    sf::CircleShape circle(width / 4);
    sf::CircleShape circle2(width / 8);

    circle2.setFillColor(sf::Color(0, 0, 255));

    for (auto &drone : drones) {
        circle.setFillColor(idToColor(drone->getId()));
        auto dronePos = drone->getPosition().tile->getPosition();
        auto orientation = drone->getPosition().orientation;
        circle.setPosition(
        dronePos.x * width + width / 4, dronePos.y * width + width / 4);
        window.draw(circle);

        std::size_t xOr = orientation == 4 ? 1 : orientation == 2 ? 6
                                                                  : 3;
        std::size_t yOr = orientation == 3 ? 1 : orientation == 1 ? 6
                                                                  : 3;
        circle2.setPosition(dronePos.x * width + width / 8 * xOr,
        dronePos.y * width + width / 8 * yOr);
        window.draw(circle2);
    }
}

auto showLogs(
sf::RenderWindow &window, gamestate::GameState &gameState, sf::Font &font)
{
    auto logs = gameState.getActions(100);
    auto mapDims = gameState.getMapDimensions();
    double width = (double)window.getSize().y / mapDims.height;

    for (std::size_t i = 0; i < logs.size(); i++) {
        std::stringstream ss;
        if (logs[i].drone) {
            ss << "T" << logs[i].drone->getId() << ": "
               << logs[i].action->str();
            sf::Text text(ss.str(), font, 20);
            text.setPosition(width * mapDims.width + 10, i * 20);
            text.setFillColor(idToColor(logs[i].drone->getId()));
            window.draw(text);

        } else {
            ss << "SERVER: " << logs[i].action->str();
            sf::Text text(ss.str(), font, 20);
            text.setPosition(width * mapDims.width + 10, i * 20);
            text.setFillColor(sf::Color::White);
            window.draw(text);
        }
    }
}

auto showInventories(
sf::RenderWindow &window, gamestate::GameState &gameState, sf::Font &font)
{
    auto drones = gameState.getDrones();
    auto mapDims = gameState.getMapDimensions();
    double width = (double)window.getSize().y / mapDims.height;
    int i = 0;
    std::reverse(drones.begin(), drones.end());
    for (auto &drone : drones) {
        std::stringstream ss;
        ss << "T" << drone->getId() << " (" << drone->getTeam() << "/" << drone->getLevel() << "): ";
        for (int i = 0; i < 7; i++) {
            ss << drone->getRessource(static_cast<gamestate::Ressource>(i))
               << " ";
        }
        sf::Text text(ss.str(), font, 20);
        text.setPosition(mapDims.width * width + 500, 200 + i * 20);
        i++;
        text.setFillColor(idToColor(drone->getId()));
        window.draw(text);
    }
}

auto showLevels(sf::RenderWindow &window, gamestate::GameState &gameState, sf::Font &font)
{
    auto drones = gameState.getDrones();
    auto mapDims = gameState.getMapDimensions();
    double width = (double)window.getSize().y / mapDims.height;

    for (std::size_t i = 1; i <= 8; i++) {
        std::size_t count = 0;
        for (auto &drone : drones) {
            if (drone->getLevel() == i)
                count++;
        }
        std::stringstream ss;
        ss << "LVL " << i << ": " << count;
        sf::Text text(ss.str(), font, 20);
        text.setPosition(mapDims.width * width + 900, 200 + i * 20);
        text.setFillColor(sf::Color::White);
        window.draw(text);
    }
}

void showDeaths(sf::RenderWindow &window, gamestate::GameState &gameState, sf::Font &font)
{
    auto deaths = gameState.getDeathCount();
    auto mapDims = gameState.getMapDimensions();
    double width = (double)window.getSize().y / mapDims.height;
    std::stringstream ss;
    ss << "Deaths: " << deaths;
    sf::Text text(ss.str(), font, 20);
    text.setPosition(mapDims.width * width + 500, 150);
    text.setFillColor(sf::Color::White);
    window.draw(text);
}

auto zappy::CoreDebug::_showMap() -> void
{
    auto &gameState = Bean<gamestate::GameState>::getInstance();

    drawGrid(_window, gameState);
    drawDrone(_window, gameState);
    showDroneCount(_window, gameState, _font);
    showFoodCount(_window, gameState, _font);
    showLogs(_window, gameState, _font);
    showInventories(_window, gameState, _font);
    showLevels(_window, gameState, _font);
    showDeaths(_window, gameState, _font);
}

auto zappy::CoreDebug::start(void) -> bool
{
    _window.clear();
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
    }
    _showMap();
    Bean<animation::AnimationManager>::getInstance().renderDebug(_window);
    _window.display();
    return _window.isOpen();
}
