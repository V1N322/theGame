#pragma once

#include "coordinates.h"

class Game {
    Coordinates mapSize;

public:
    void create_map(Coordinates size);
    const Coordinates& get_mapSize() const;
    Coordinates get_playerPos() const;
};
