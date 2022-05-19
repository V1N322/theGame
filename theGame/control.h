#pragma once

class Controller
{

	Game game;

public:
	Controller()
	{}
	Controller(Game aMap)
		:game(aMap)
	{}

	virtual ~Controller() = default;

	virtual void start() = 0;

};