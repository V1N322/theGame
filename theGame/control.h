#pragma once

#include "game.h"

class Controller {

    Game game;

public:
    Controller()
    {
    }

    Controller(Game aMap)
        : game(aMap)
    {
    }

    virtual ~Controller() = default;

    void start();
};
