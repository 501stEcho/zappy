/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Animation.hpp
*/

#pragma once

#include "AnimationManager/Animation.hpp"
#include "Beans/Bean.hpp"
#include "GameState/Types/Tile.hpp"
#include "GameState/Types/Drone.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <cstddef>
#include <SFML/Graphics.hpp>
#include <iostream>


namespace animation
{
    class MoveAnimation : public Animation
    {
    public:
        MoveAnimation(gamestate::DroneRef drone)
            : Animation(MOVE, drone, 100, false)
        {
        }

        void keyframeDebug(std::size_t frame, sf::RenderWindow &window)
        {
            _drone->getId();
        }

        void keyframe3D(std::size_t frame)
        {
            (void)frame;
        }
    };
}