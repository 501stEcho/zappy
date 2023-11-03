/*
** EPITECH PROJECT, 2023
** MapHandler
** File description:
** zappy
*/

#pragma once

#include "Renderer/Vector.hpp"
#include "Beans/Bean.hpp"
#include "GameState/GameState.hpp"

namespace zappy
{

    class MapHandlerException : public std::exception {
        public:
            MapHandlerException(std::string reason) : _reason(reason) {};
            const char *what() const noexcept override
            {
                return _reason.c_str();
            }
        private:
            std::string _reason;
    };

    class MapHandler {
        public:
            MapHandler();
            void updateMapInfos();
            Vec3<float> getTilePosition(unsigned int i, unsigned int j);
            Vec3<float> getPlayerPosition(unsigned int id);
            gamestate::Dimensions getMapDimensions();
            ~MapHandler();

        private:
            void _computeTilePosition(void);
            void _computePlayerPosition(void);

            std::vector<std::vector<Vec3<float>>> _tilePositions;
            std::map<unsigned int, Vec3<float>> _playersPosition;

            unsigned int _playersNb;
            gamestate::Dimensions _mapDimensions;
            float _offset;
    };
}
