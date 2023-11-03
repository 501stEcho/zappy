/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** AnimationManager.hpp
*/

#pragma once

#include "AnimationManager/Animation.hpp"
#include "GameState/Types/Types.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <cstddef>
#include <mutex>

namespace animation {
    class Animation;

    class AnimationManager {
        public:
            AnimationManager();
            auto playAnimation(std::unique_ptr<Animation> animation) -> void;
            auto clearLambda(std::function<bool(std::unique_ptr<Animation> &)> lambda) -> void;
            auto renderDebug(sf::RenderWindow &window) -> void;
            auto render3D() -> void;
        private:
            std::mutex _mutex;
            auto _clearFinishedAnimation() -> void;
            std::vector<std::unique_ptr<Animation>> _playingAnimation;
    };
}