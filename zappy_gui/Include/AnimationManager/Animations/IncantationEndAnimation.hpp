/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Animation.hpp
*/

#pragma once

#include "AnimationManager/Animation.hpp"
#include "Beans/Bean.hpp"
#include "Core/MapHandler.hpp"
#include "GameState/Types/Tile.hpp"
#include "GameState/Types/Types.hpp"
#include "Renderer/ParticlesManager.hpp"
#include "Renderer/Renderer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cstddef>
#include <iostream>
#include <raylib.h>

namespace animation
{
    class IncantationEndAnimation : public Animation
    {
    public:
        IncantationEndAnimation(gamestate::TileRef tile)
            : Animation(INCANTATION_END, tile, 100, false)
        {
        }

        void keyframeDebug(std::size_t frame, sf::RenderWindow &window)
        {
            auto mapDims = Bean<gamestate::GameState>::getInstance().getMapDimensions();
            double width = (double)window.getSize().y / mapDims.height;
            auto tilePos = _tile->getPosition();
            auto squareWidth = width * frame / 50.0;
            sf::RectangleShape rectangle(sf::Vector2f(squareWidth, squareWidth));
            rectangle.setFillColor(sf::Color::Transparent);
            rectangle.setOutlineColor(sf::Color::Yellow);
            rectangle.setOutlineThickness(3);
            rectangle.setOrigin(squareWidth / 2, squareWidth / 2);
            rectangle.setPosition(tilePos.x * width + width / 2, tilePos.y * width + width / 2);
            window.draw(rectangle);
        }

        void keyframe3D(std::size_t frame)
        {
            (void)frame;
            zappy::MapHandler &handler = Bean<zappy::MapHandler>::getInstance();

            try {
                zappy::Vec3<float> pos = handler.getTilePosition(_tile->getPosition().y, _tile->getPosition().x);
                Bean<ParticleManager>::getInstance().addParticles({pos.x, 6, pos.z}, 2, {0.01, 0.05, 0.01}, YELLOW, NEG);
            } catch (std::exception &err) {
                std::cout << err.what() << std::endl;
            }
        }
    };
}