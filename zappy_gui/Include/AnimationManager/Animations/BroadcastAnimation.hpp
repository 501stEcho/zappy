/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Animation.hpp
*/

#pragma once

#include "AnimationManager/Animation.hpp"
#include "AnimationManager/AnimationManager.hpp"
#include "Beans/Bean.hpp"
#include "Core/MapHandler.hpp"
#include "Renderer/ParticlesManager.hpp"
#include "Renderer/Renderer.hpp"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <iostream>
#include <raylib.h>

namespace animation
{
    class BroadcastAnimation : public Animation
    {
    public:
        BroadcastAnimation(gamestate::TileRef tile, std::string msg)
            : Animation(BROADCAST, tile, 100, false), _msg(msg)
        {
            AnimationManager &animManager = Bean<AnimationManager>::getInstance();
            animManager.clearLambda([&](std::unique_ptr<Animation> &anim) -> bool {
                if (anim->getType() != animation::Type::BROADCAST)
                    return false;
                auto pos = anim->getTile()->getPosition();
                auto refPos = tile->getPosition();
                return (pos.x == refPos.x && pos.y == refPos.y);
            });
        }

        void keyframeDebug(std::size_t frame, sf::RenderWindow &window)
        {
            auto mapDims = Bean<gamestate::GameState>::getInstance().getMapDimensions();
            double width = (double)window.getSize().y / mapDims.height;
            auto tilePos = _tile->getPosition();
            sf::CircleShape circle(0.5f);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color::Green);
            circle.setOutlineThickness(3);
            circle.setRadius((frame / 100.0) * window.getSize().y);
            circle.setOrigin(circle.getRadius(), circle.getRadius());
            circle.setPosition(tilePos.x * width + width / 2, tilePos.y * width + width / 2);

            window.draw(circle);
        }

        void keyframe3D(std::size_t frame)
        {
            (void)frame;
            zappy::Renderer &renderer = Bean<zappy::Renderer>::getInstance();
            zappy::MapHandler &handler = Bean<zappy::MapHandler>::getInstance();

            try {
                zappy::Vec3<float> pos = handler.getTilePosition(_tile->getPosition().y, _tile->getPosition().x);
                pos.y += 3;
                renderer.drawTextInImage("chatbox", _msg, pos, 60, BLACK);
                Bean<ParticleManager>::getInstance().addParticles({pos.x, 1, pos.z}, 1, {0.1, 0.0, 0.1}, GREEN, DOUBLE);
            } catch (std::exception &err) {
                std::cout << err.what() << std::endl;
            }
        }

    private:
        std::string _msg;
    };
}