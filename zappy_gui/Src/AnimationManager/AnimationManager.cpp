/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** AnimationManager.hpp
*/


#include "AnimationManager/AnimationManager.hpp"
#include "AnimationManager/Animation.hpp"
#include "GameState/Types/Types.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <cstddef>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

animation::AnimationManager::AnimationManager()
{
}

auto animation::AnimationManager::playAnimation(std::unique_ptr<Animation> animation) -> void
{
    std::lock_guard<std::mutex> lock(_mutex);
    _playingAnimation.push_back(std::move(animation));
}

auto animation::AnimationManager::_clearFinishedAnimation() -> void
{
    _playingAnimation.erase(
        std::remove_if(
            _playingAnimation.begin(),
            _playingAnimation.end(),
            [](const auto& animation) { return animation->isFinished(); }
        ),
        _playingAnimation.end()
    );
}

auto animation::AnimationManager::clearLambda(std::function<bool(std::unique_ptr<Animation> &)> lambda) -> void
{
    std::lock_guard<std::mutex> lock(_mutex);
    _playingAnimation.erase(
        std::remove_if(
            _playingAnimation.begin(),
            _playingAnimation.end(),
            lambda
        ),
        _playingAnimation.end()
    );
}

auto animation::AnimationManager::renderDebug(sf::RenderWindow &window) -> void
{
    std::lock_guard<std::mutex> lock(_mutex);
    _clearFinishedAnimation();

    for (auto& animation : _playingAnimation) {
        animation->nextDebug(window);
    }
}

auto animation::AnimationManager::render3D() -> void
{
    std::lock_guard<std::mutex> lock(_mutex);
    _clearFinishedAnimation();

    for (auto& animation : _playingAnimation) {
        animation->next3D();
    }
}