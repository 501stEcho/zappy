/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** UserInterface.hpp
*/

#pragma once

#include "AnimationManager/AnimationManager.hpp"
#include "ICore.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <cstddef>
#include <vector>

namespace zappy
{
    class CoreDebug : public ICore
    {
    public:
        CoreDebug();
        ~CoreDebug();

        auto start(void) -> bool;

    private:
        auto _showMap() -> void;
        sf::Font _font;
        sf::RenderWindow _window;
    };
}