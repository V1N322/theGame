#include "game.h"

void Game::create_map(Coordinates size)
{
    mapSize = size;
}

const Coordinates& Game::get_mapSize() const
{
    return mapSize;
}

Coordinates Game::get_playerPos() const
{
    static Coordinates dummy(10, 10);
    return dummy;
}
