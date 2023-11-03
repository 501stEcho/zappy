/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** Client
*/

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

#include "GameState/GameState.hpp"
#include "GameState/Types/Types.hpp"

Test(GameState, setMapDimensions)
{
    gamestate::GameState gameState;

    gameState.setMapDimensions(10, 10);

    gamestate::Dimensions dimensions = gameState.getMapDimensions();

    cr_assert_eq(dimensions.width, 10);
    cr_assert_eq(dimensions.height, 10);

    gamestate::TileRef tile = gameState.getTile(5, 5);

    cr_assert_eq(tile->getPosition().x, 5);

    gamestate::TileRef tile2 = gameState.getTile(15, 5);

    cr_assert_null(tile2);
}

Test(GameState, resizeMap)
{
    gamestate::GameState gameState;

    gameState.setMapDimensions(10, 10);
    gameState.setMapDimensions(20, 20);

    gamestate::Dimensions dimensions = gameState.getMapDimensions();

    cr_assert_eq(dimensions.width, 10);
    cr_assert_eq(dimensions.height, 10);

    gamestate::TileRef tile = gameState.getTile(15, 5);

    cr_assert_eq(tile->getPosition().x, 15);

    gamestate::TileRef tile2 = gameState.getTile(20, 5);

    cr_assert_null(tile2);
}
