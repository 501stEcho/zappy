/*
** EPITECH PROJECT, 2023
** Core3D
** File description:
** zappy
*/

#include "Core/Core3D.hpp"
#include "AnimationManager/AnimationManager.hpp"
#include "Renderer/ParticlesManager.hpp"
#include <raylib.h>
#include <sstream>
#include <string>

zappy::Core3D::Core3D()
{
    auto &renderer = Bean<Renderer>::getInstance();
    MapHandler &handler = Bean<MapHandler>::getInstance();

    renderer.setAmbientColors("Sources/png/ambientGradient.png");

    renderer.addObject("character", "Sources/model/character.obj");
    renderer.addObject("island", "Sources/model/tile.obj");

    renderer.addShader("materialshader", "Sources/shaders/material.vs", "Sources/shaders/material.fs");
    renderer.addShader("textureshader", "Sources/shaders/texture.vs", "Sources/shaders/texture.fs");

    renderer.addTexture("bluecard", "Sources/png/purpleCard.png");
    renderer.addTexture("orangecard", "Sources/png/orangeCard.png");
    renderer.addTexture("food", "Sources/png/food.png");
    renderer.addTexture("linemate", "Sources/png/Linemate.png");
    renderer.addTexture("deraumere", "Sources/png/Deraumere.png");
    renderer.addTexture("sibur", "Sources/png/Sibur.png");
    renderer.addTexture("mendiane", "Sources/png/Mendiane.png");
    renderer.addTexture("phiras", "Sources/png/Phiras.png");
    renderer.addTexture("thystame", "Sources/png/Thystame.png");
    renderer.addTexture("chatbox", "Sources/png/chatbox.png");

    renderer.setObjectShader("character", "textureshader");
    renderer.setObjectShader("island", "textureshader");

    renderer.setSkybox("Sources/hdr/skybox.hdr", "Sources/shaders/skybox.vs",
    "Sources/shaders/skybox.fs", "Sources/shaders/cubemap.vs", "Sources/shaders/cubemap.fs");

    _offset = 2.5;

    handler.updateMapInfos();

    renderer.addDirectionalLight(zappy::Vec3<float>(0, 3, 0), zappy::Vec3<float>(0, 0, 0), WHITE, true, 40.0f * _offset);
    _tileSelected = false;
    _selectedTileIndex = zappy::Vec2<unsigned int>(0, 0);
}

bool zappy::Core3D::start()
{
    gamestate::GameState &gamestate = Bean<gamestate::GameState>::getInstance();
    Renderer &renderer = Bean<Renderer>::getInstance();
    MapHandler &maphandler = Bean<MapHandler>::getInstance();
    auto &animationManager = Bean<animation::AnimationManager>::getInstance();

    maphandler.updateMapInfos();
    renderer.actualize();
    renderer.enableDrawing();

    /*
        Display of the scene in 3D
    */
    renderer.enable3DMode();

    renderer.displayLights();
    renderer.displaySkybox();
    animationManager.render3D();
    Bean<ParticleManager>::getInstance().render();
    _displayBoard(renderer, maphandler);
    _displayPlayer(renderer, gamestate);

    Bean<animation::AnimationManager>::getInstance().render3D();

    renderer.disable3DMode();

    /*
        All 2D effects and displaying
    */
    _winScreen(renderer, gamestate);
    _displaySelectionData(renderer, gamestate);

    renderer.disableDrawing();

    // Reset selection of tile
    _tileSelected = false;
    _playerSelected = false;
    _target.setHit(false);
    return (renderer.stillActive());
}

void zappy::Core3D::_winScreen(Renderer &renderer, gamestate::GameState &gamestate)
{
    if (!gamestate.isWinnerSet())
        return;
    std::string winner = gamestate.getWinner();
    std::string text = "The winner is : " + winner;

    float width = renderer.getWindowWidth();
    float height = renderer.getWindowHeight();

    Vec2<float> pos = Vec2<float>(width / 2 - 200, height / 2 - 50);

    renderer.drawText(text, pos, 30, WHITE);
}

void zappy::Core3D::_displayTile(Renderer &renderer, MapHandler &handler, unsigned int i, unsigned j)
{
    try {
        CollisionPoint tileCollision;
        Vec3<float> pos = handler.getTilePosition(i, j);

        tileCollision = renderer.GetCollision("island", handler.getTilePosition(i, j));
        if (tileCollision.hit() && (!_target.hit() || tileCollision.distance() < _target.distance())) {
            _selectedTileIndex.x = j;
            _selectedTileIndex.y = i;
            _tileSelected = true;
            _target = tileCollision;
        }

        renderer.displayObject("island", pos);
    } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
    }
}

void zappy::Core3D::_displayBoard(Renderer &renderer, MapHandler &handler)
{
    gamestate::Dimensions dim = handler.getMapDimensions();

    for (unsigned int i = 0; i < dim.height; i++) {
        for (unsigned int j = 0; j < dim.width; j++) {
            _displayTile(renderer, handler, i, j);
        }
    }
}

void zappy::Core3D::_displaySelectionData(Renderer &renderer, gamestate::GameState &gamestate)
{
    if (_tileSelected)
        _displaySelectedTile(renderer, gamestate);
    else if (_playerSelected)
        _displaySelectedPlayer(renderer, gamestate);
    else
        return;
}

void zappy::Core3D::_displaySelectedTile(Renderer &renderer, gamestate::GameState &gamestate)
{
    float x = renderer.getWindowWidth() - renderer.getWindowWidth() / 7;
    float y = renderer.getWindowHeight() / 9;
    zappy::MapHandler &handler = Bean<zappy::MapHandler>::getInstance();

    if (!_tileSelected)
        return;
    Vec2<float> position(x, y);
    Vec2<float> textPosition(x, y);
    unsigned int nb;

    std::map<gamestate::Ressource, std::string> icons = {
    {gamestate::Ressource::FOOD, "food"},
    {gamestate::Ressource::LINEMATE, "linemate"},
    {gamestate::Ressource::DERAUMERE, "deraumere"},
    {gamestate::Ressource::SIBUR, "sibur"},
    {gamestate::Ressource::MENDIANE, "mendiane"},
    {gamestate::Ressource::PHIRAS, "phiras"},
    {gamestate::Ressource::THYSTAME, "thystame"}};

    renderer.enableBlendMode();
    renderer.displayTexture("bluecard", 3, position);

    position.x *= 1.02;
    position.y *= 1.7;
    textPosition = Vec2<float>(position.x * 1.06, position.y * 1.085);

    for (auto &ressource : icons) {
        nb = gamestate.getTile(_selectedTileIndex.x, _selectedTileIndex.y)->getRessource(ressource.first);
        renderer.displayTexture(ressource.second, 1.5, position);
        renderer.drawText(_formatQuantity(nb), textPosition, 30, WHITE);
        position.y += renderer.getWindowHeight() / 11.5;
        textPosition.y += renderer.getWindowHeight() / 11.5;
    }
    renderer.disableBlendMode();

    renderer.enable3DMode();
    Vec3<float> pos = handler.getTilePosition(_selectedTileIndex.y, _selectedTileIndex.x);
    renderer.displayBoundingBox("island", pos);
    renderer.disable3DMode();
}

void zappy::Core3D::_displaySelectedPlayer(Renderer &renderer, gamestate::GameState &gamestate)
{
    float x = renderer.getWindowWidth() - renderer.getWindowWidth() / 7;
    float y = renderer.getWindowHeight() / 9;
    zappy::MapHandler &handler = Bean<zappy::MapHandler>::getInstance();

    if (!_playerSelected)
        return;
    Vec2<float> position(x, y);
    Vec2<float> textPosition(x, y);
    unsigned int nb;

    std::map<gamestate::Ressource, std::string> icons = {
    {gamestate::Ressource::FOOD, "food"},
    {gamestate::Ressource::LINEMATE, "linemate"},
    {gamestate::Ressource::DERAUMERE, "deraumere"},
    {gamestate::Ressource::SIBUR, "sibur"},
    {gamestate::Ressource::MENDIANE, "mendiane"},
    {gamestate::Ressource::PHIRAS, "phiras"},
    {gamestate::Ressource::THYSTAME, "thystame"}};

    position.y -= 50;
    renderer.enableBlendMode();
    renderer.displayTexture("orangecard", 3, position);
    position.y += 50;

    position.x *= 1.02;
    position.y *= 1.7;
    textPosition = Vec2<float>(position.x * 1.06, position.y * 1.085);
    auto drone = gamestate.getDrone(_selectedPlayerID);
    auto level = drone->getLevel();
    auto team = drone->getTeam();

    if (team.size() > 2)
        team = team.substr(0, 2);

    renderer.drawText(team, {position.x, position.y - 90}, 30, WHITE);
    renderer.drawText(std::to_string(level), {position.x + 120, position.y - 90}, 30, WHITE);

    for (auto &ressource : icons) {
        nb = drone->getRessource(ressource.first);
        renderer.displayTexture(ressource.second, 1.5, position);
        renderer.drawText(_formatQuantity(nb), textPosition, 30, WHITE);
        position.y += renderer.getWindowHeight() / 11.5;
        textPosition.y += renderer.getWindowHeight() / 11.5;
    }
    renderer.disableBlendMode();

    renderer.enable3DMode();
    try {
        Vec3<float> pos = handler.getPlayerPosition(_selectedPlayerID);
        renderer.displayBoundingBox("character", pos);
    } catch (std::exception &err) {
    };
    renderer.disable3DMode();
}

void zappy::Core3D::_displayPlayer(Renderer &renderer, gamestate::GameState &gamestate)
{
    std::vector<gamestate::DroneRef> drones = gamestate.getDrones();
    MapHandler &handler = Bean<MapHandler>::getInstance();

    CollisionPoint tileCollision;

    Vec3<float> position;
    Vec3<float> orientation;
    gamestate::Coordinates tile;
    gamestate::Orientation side;

    handler.updateMapInfos();
    for (unsigned int i = 0; i < drones.size(); i++) {
        tile = drones[i]->getPosition().tile->getPosition();
        side = drones[i]->getPosition().orientation;

        switch (side) {
        case (gamestate::NORTH):
            orientation.y = 90;
            break;
        case (gamestate::EAST):
            orientation.y = 180;
            break;

        case (gamestate::SOUTH):
            orientation.y = 270;
            break;

        case (gamestate::WEST):
            orientation.y = 0;
            break;
        }

        try {
            position = handler.getPlayerPosition(drones[i]->getId());
            tileCollision = renderer.GetCollision("character", position);
            if (tileCollision.hit() && (!_target.hit() || tileCollision.distance() < _target.distance())) {
                _selectedPlayerID = drones[i]->getId();
                _tileSelected = false;
                _playerSelected = true;
                _target = tileCollision;
            }
            renderer.displayObject("character", position, orientation);
        } catch (std::exception &err) {
        };
    }
}

std::string zappy::Core3D::_formatQuantity(unsigned int nb)
{
    if (nb > 999)
        return ("999+");
    return (std::to_string(nb));
}

zappy::Core3D::~Core3D()
{
    auto &renderer = Bean<Renderer>::getInstance();

    renderer.unloadAllAssets();
}
