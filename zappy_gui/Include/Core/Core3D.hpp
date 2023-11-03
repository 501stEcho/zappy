/*
** EPITECH PROJECT, 2023
** Core
** File description:
** zappy
*/

#pragma once

#include "Renderer/Renderer.hpp"
#include "GameState/GameState.hpp"
#include "AnimationManager/AnimationManager.hpp"
#include "Core/MapHandler.hpp"
#include "Beans/Bean.hpp"
#include "ICore.hpp"

namespace zappy
{
    class CoreException : public std::exception {
        public:
            CoreException(std::string reason) : _reason(reason) {}
            const char *what() const noexcept override
            {
                return (_reason.c_str());
            }
        private:
            std::string _reason;
    };

    class Core3D: public ICore {
        public:
            Core3D();
            ~Core3D();

            bool start();
        private:
            void _displayBoard(Renderer &renderer, MapHandler &handler);
            void _displayTile(Renderer &renderer, MapHandler &handler, unsigned int i, unsigned int j);
            void _displayPlayer(Renderer &renderer, gamestate::GameState &gamestate);

            void _displaySelectionData(Renderer &renderer, gamestate::GameState &gamestate);
            void _displaySelectedTile(Renderer &renderer, gamestate::GameState &gamestate);
            void _winScreen(Renderer &renderer, gamestate::GameState &gamestate);
            void _displaySelectedPlayer(Renderer &renderer, gamestate::GameState &gamestate);
            /*
                Tools methods
            */
            std::string _formatQuantity(unsigned int nb);

            float _offset;

            bool _tileSelected;
            bool _playerSelected;
            Vec2<unsigned int> _selectedTileIndex;
            CollisionPoint _target;
            unsigned int _selectedPlayerID;
    };

}
