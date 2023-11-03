/*
** EPITECH PROJECT, 2023
** MapHandler
** File description:
** zappy
*/

#include "Core/MapHandler.hpp"

zappy::MapHandler::MapHandler()
{
    _offset = 2.5;
    updateMapInfos();
}

void zappy::MapHandler::updateMapInfos()
{
    gamestate::Dimensions dim =  Bean<gamestate::GameState>::getInstance().getMapDimensions();
	if (!(dim.height == _mapDimensions.height && dim.width == _mapDimensions.width)) {
    	_mapDimensions = dim;
		_computeTilePosition();
	}
	_computePlayerPosition();
}

zappy::Vec3<float> zappy::MapHandler::getTilePosition(unsigned int i, unsigned int j)
{
    if (i >= _tilePositions.size() || j >= _tilePositions[i].size()) {
        throw MapHandlerException(std::to_string(i) + " " + std::to_string(j) + " : index out of range");
    }
    return _tilePositions[i][j];
}

zappy::Vec3<float> zappy::MapHandler::getPlayerPosition(unsigned int index)
{
	if (_playersPosition.find(index) == _playersPosition.end())
		throw MapHandlerException(std::to_string(index) + " : No players with that ID");
	return (_playersPosition.at(index));
}

gamestate::Dimensions zappy::MapHandler::getMapDimensions()
{
    return _mapDimensions;
}

void zappy::MapHandler::_computeTilePosition(void)
{
	Vec3<float> position;

	for (unsigned int i = 0; i < _tilePositions.size(); i++) {
		_tilePositions[i].clear();
	}
	_tilePositions.clear();

	for (unsigned int i = 0; i < _mapDimensions.height; i++) {
		_tilePositions.push_back(std::vector<Vec3<float>>());
		for (unsigned int j = 0; j < _mapDimensions.width; j++) {
			position.x = _offset * (static_cast<float>(i) - static_cast<float>(_mapDimensions.height) / 2);
			position.y = 0;
			position.z = _offset * (static_cast<float>(j) - static_cast<float>(_mapDimensions.width) / 2);
			_tilePositions[i].push_back(position);
		}
	}
}

void zappy::MapHandler::_computePlayerPosition(void)
{
	std::vector<gamestate::DroneRef> drones = Bean<gamestate::GameState>::getInstance().getDrones();
	std::map<gamestate::Coordinates, std::vector<unsigned int>> playersByTile;

	_playersNb = drones.size();
	_playersPosition.clear();
	for (unsigned int i = 0; i < _playersNb; i++) {
		gamestate::Coordinates tile = drones[i]->getPosition().tile->getPosition();
		if (playersByTile.find(tile) == playersByTile.end()) {
			std::vector<unsigned int> vec;
			vec.push_back(drones[i]->getId());
			playersByTile.insert({tile, vec});
		} else
			playersByTile.at(tile).push_back(drones[i]->getId());
	}

	unsigned int droneOnTile;
	Vec3<float> tilePos;
	Vec3<float> pos;
	gamestate::Coordinates coordinates;
	unsigned int divNb;
	float tileSize = _offset * 0.8;
	for (auto &it : playersByTile) {
		coordinates = it.first;
		droneOnTile = it.second.size();
		tilePos = getTilePosition(coordinates.y, coordinates.x);
		pos = tilePos;
		pos.y += 0.5;
		if (droneOnTile > 4)
			divNb = 3;
		else if (droneOnTile > 1)
			divNb = 2;
		else
			divNb = 1;

		for (unsigned int i = 0; i < droneOnTile; i++) {
			if (i >= divNb * divNb)
				break;
			if (divNb != 1) {
				pos.z = tilePos.z + static_cast<float>((i / divNb % divNb) * (tileSize / divNb)) - (tileSize / (6 - divNb));
				pos.x = tilePos.x + static_cast<float>((i % divNb) * (tileSize / divNb)) - (tileSize / (6 - divNb));
			} else {
				pos.z = tilePos.z + (i / divNb) * (tileSize / divNb);
				pos.x = tilePos.x + (i % divNb) * (tileSize / divNb);
			}
			_playersPosition.insert({it.second[i], pos});
		}
	}
}


zappy::MapHandler::~MapHandler()
{
}
