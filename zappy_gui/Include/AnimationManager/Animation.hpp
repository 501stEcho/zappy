/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Animation.hpp
*/

#pragma once

#include "Beans/Bean.hpp"
#include "GameState/Types/Types.hpp"
#include "Core/MapHandler.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstddef>

namespace animation {

 class Animation {
        public:
            Animation(animation::Type type, gamestate::DroneRef drone, std::size_t nFrames, bool loop = true)
            :_type(type), _drone(drone), _tile(nullptr), _totalFrames(nFrames), _currentFrame(0), _loop(loop) {}
            Animation(animation::Type type, gamestate::TileRef tile, std::size_t nFrames, bool loop = true)
            :_type(type), _drone(nullptr), _tile(tile), _totalFrames(nFrames), _currentFrame(0), _loop(loop) {}

            virtual ~Animation() = default;

            virtual void keyframeDebug(std::size_t frame, sf::RenderWindow &window) = 0;
            virtual void keyframe3D(std::size_t frame) = 0;

            void nextDebug(sf::RenderWindow &window) {
                _incrementFrame();
                keyframeDebug(_currentFrame, window);
            }

            void next3D() {
                _incrementFrame();
                keyframe3D(_currentFrame);
            }

            bool isFinished() const {
                return !_loop && _currentFrame == _totalFrames;
            }

            animation::Type getType() const {
                return _type;
            }

            auto getTile() const -> gamestate::TileRef {
                return _tile;
            }

            auto getDrone() const -> gamestate::DroneRef {
                return _drone;
            }

            private:
                void _incrementFrame() {
                    if (_currentFrame < _totalFrames)
                        _currentFrame++;
                    else if (_loop)
                        _currentFrame = 0;
                }

            protected:
                animation::Type _type;
                gamestate::DroneRef _drone;
                gamestate::TileRef _tile;
                std::size_t _totalFrames;
                std::size_t _currentFrame;
                bool _loop;
    };
}