#pragma once

class Game
{
	Coordinates mapSize;

public:
	virtual ~Game() = default;

	virtual create_map(Coordinates size) = 0;
};