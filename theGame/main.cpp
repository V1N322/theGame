#include "theGame.h"








auto inputStep(Coordinates mapSize, Coordinates playerPos)
{

	using KeyState = decltype(GetKeyState('A'));
	using KeyState = decltype(GetKeyState('W'));
	using KeyState = decltype(GetKeyState('S'));
	using KeyState = decltype(GetKeyState('D'));
	KeyState pressedMask = static_cast<KeyState>(1 << (sizeof(KeyState) * CHAR_BIT - 1));

	Coordinates newPos(playerPos.x, playerPos.y);

	//Button button;


	if ((GetKeyState('W') & pressedMask) != 0) {
		--newPos.y;
		if (newPos.y == -1)
			++newPos.y;
	}
	if ((GetKeyState('A') & pressedMask) != 0)
	{
		--newPos.x;
		if (newPos.x == -1)
			++newPos.x;
	}

	if ((GetKeyState('S') & pressedMask) != 0)
	{
		++newPos.y;
		if (newPos.y == mapSize.y)
			--newPos.y;
	}

	if ((GetKeyState('D') & pressedMask) != 0)
	{
		++newPos.x;
		if (newPos.x == mapSize.x)
			--newPos.x;
	}



	return newPos;
}


class Logic
{



};

class Game
{
	Map map;
	Actor player;


public:
	Game(Map aMap)
		: map(aMap), player(aMap.get_actor())
	{	}

	
	void view(int FOV)
	{
		renderYan(FOV, map);
	}

};



int main()
{
	int PFC = 0;

	Map map;
	Game game(map);
	



	while (true)
	{
		system("cls");

		std::cout << "PFC = [" << PFC << "]" << '\n';

		game.view(5);



		++PFC;
	}
	system("cls");
	std::cout << "You are dead!";

	return 0;
}