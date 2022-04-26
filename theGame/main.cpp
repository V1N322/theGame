#include "theGame.h"

class Game 
{
public:
	Coordinates mapSize;
	Coordinates playerPos;

	Game(const Coordinates& aMapSize, const Coordinates& aPlayerPos)
		:mapSize(aMapSize), playerPos(aPlayerPos)
	{
		mapSize = aMapSize;
		playerPos = aPlayerPos;
	}
		
};

int main()
{

	Coordinates mapSize(10, 10);
	Coordinates playerPos(5, 5);

	//Processed Frames Count
	int PFC = 0;

	Game game(mapSize, playerPos);

	while (true)
	{
		std::cout << "FPP = [" << PFC << "]" << std::endl;

		game.input();
		game.showPosPlayer();
		
		
	
		++PFC
	}

	return 0;
}