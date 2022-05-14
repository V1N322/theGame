#include "theGame.h"

enum class MoveType
{
	oneStep,
	input
};

enum class RenderType
{
	fullMap,
	yanMoment,
	twoView,
	inventory
};

RenderType viewType = RenderType::yanMoment;

void changeView(char pressedButton = 'n')
{
	//if (viewType == RenderType::fullMap)
		//viewType = RenderType::yanMoment;

	if (viewType != RenderType::yanMoment && pressedButton == 'n')
		viewType = RenderType::yanMoment;

	else if (pressedButton == 'v')
	{
		if (viewType == RenderType::inventory)
			viewType = RenderType::yanMoment;
		else
			viewType = RenderType::inventory;
	}
	


	//else if (viewType == RenderType::twoView)
		//viewType = RenderType::fullMap;
}

class Render
{

	void buildUpFull(Coordinates mapSize)
	{
		for (int i = -2; i != mapSize.x * 2; ++i)
			std::cout << '*';
		std::cout << '\n';
	}

	void buildBaseFull(Coordinates mapSize, Coordinates playerPos)
	{

		for (int b = 0; b != mapSize.y; b++) {

			std::cout << '*';

			for (int i = 0; i != mapSize.x; ++i)
			{



				if (b == playerPos.y && i == playerPos.x) {

					std::cout << 'P';


					std::cout << ' ';

				}
				std::cout << '*';

				std::cout << '\n';
			}

		}
	}

	void buildDownFull(Coordinates mapSize)
	{
		for (int i = -2; i != mapSize.x * 2; ++i)
			std::cout << '*';
		std::cout << '\n';
	}

public:

	void buildYan(Coordinates mapSize, Coordinates playerPos, int viewSize, Map obj)
	{

		for (int y = viewSize - viewSize * 2; y != viewSize + 1; ++y)
		{
			for (int x = -viewSize; x != viewSize + 1; ++x)
			{
				int X = x + playerPos.x;
				int Y = y + playerPos.y;

				auto& items = obj.get_items();

				std::cout << " ";
				
				bool hasStick = false;

				for (const auto& item : items)
				{
					int num = 0;
					if (item->get_pos().x == X && item->get_pos().y == Y) 
					{
						if (item->get_name() == "stick")
						{
							hasStick = true;
						}
						
					}
					++num;
				}

				if (X == playerPos.x && Y == playerPos.y)
					std::cout << 'P';

				else if (hasStick)
					std::cout << '-';


				else if (X <= -1 || X >= mapSize.x || Y <= -1 || Y >= mapSize.y)
					std::cout << '~';

				else
					std::cout << ' ';


				std::cout << " ";
			}
			std::cout << '\n';

		}


	}

public:
	void buildInventory(Inventory inventory)
	{
		std::cout << "        " << "INVENTORY" << '\n';

		for (char n : inventory.get_items())

			std::cout << '[' << n << ']';
		std::cout << '\n';
	}

public:
	void renderFullMap(Coordinates mapSize, Coordinates playerPos)
	{

		buildUpFull(mapSize);

		buildBaseFull(mapSize, playerPos);

		buildDownFull(mapSize);
	}

	void renderYan(Coordinates mapSize, Coordinates playerPos, int viewSize, Map obj)
	{
		buildYan(mapSize, playerPos, viewSize, obj);

	}

	void renderTwo(Coordinates mapSize, Coordinates playerPos, int viewSize, Map obj)
	{
		renderYan(mapSize, playerPos, viewSize, obj);
		renderFullMap(mapSize, playerPos);
	}

	void inventory(Inventory items)
	{
		buildInventory(items);
	}
};

int frogJumpInt = 0;

class Button
{
public:
	char isPressed()
	{
		char playerPressed = std::cin.get();

		return playerPressed;
	}
};

class Move
{
	
	

public:

	auto inputStep(Coordinates mapSize, Coordinates playerPos)
	{

		using KeyState = decltype(GetKeyState('A'));
		using KeyState = decltype(GetKeyState('W'));
		using KeyState = decltype(GetKeyState('S'));
		using KeyState = decltype(GetKeyState('D'));
		using KeyState = decltype(GetKeyState('V'));
		KeyState pressedMask = static_cast<KeyState>(1 << (sizeof(KeyState) * CHAR_BIT - 1));

		Coordinates newPos(playerPos.x, playerPos.y);

		Button button;


		char buttonPressed = 'f';

		if ((GetKeyState('W') & pressedMask) != 0 && viewType != RenderType::inventory) {
			--newPos.y;
			if (newPos.y == -1)
				++newPos.y;
		}
		if ((GetKeyState('A') & pressedMask) != 0 && viewType != RenderType::inventory)
		{
			--newPos.x;
			if (newPos.x == -1)
				++newPos.x;
		}

		if ((GetKeyState('S') & pressedMask) != 0 && viewType != RenderType::inventory)
		{
			++newPos.y;
			if (newPos.y == mapSize.y)
				--newPos.y;
		}

		if ((GetKeyState('D') & pressedMask) != 0 && viewType != RenderType::inventory)
		{
			++newPos.x;
			if (newPos.x == mapSize.x)
				--newPos.x;
		}

		if ((GetKeyState('N') & pressedMask) != 0)
		{
			changeView();
		}

		if ((GetKeyState('V') & pressedMask) != 0)
		{
			changeView('v');
			Sleep(100);
		}

		return newPos;
	}
};

class Logic
{
public:

	bool playerIsDead(Coordinates playerPos, Map obj)
	{
		if (obj.obj.player.actorHP.HP != obj.obj.player.actorHP.minHP)
			return false;
		if (obj.obj.player.actorHP.HP <= obj.obj.player.actorHP.minHP)
			return true;

		return false;
	}

	char takeItem(Coordinates playerPos, Map& map)
	{
		char symbol = map.stepOnItem(playerPos);

		return symbol;
	}


};

class Game
{
public:
	Coordinates mapSize;
	Coordinates playerPos;
	int viewSize = 6;
	bool isEnd = false;
	Inventory inventory;
	Map mapOBJ;

	

	Game(const Coordinates& aMapSize, const Coordinates& aPlayerPos, const Map& aObjects)
		:mapSize(aMapSize), playerPos(aPlayerPos), mapOBJ(aObjects)
	{
		mapSize = aMapSize;
		playerPos = aPlayerPos;
	}


public:
	void showPosPlayer()
	{
		std::cout << "the player is on " << "[X = " << playerPos.x << ", Y = " << playerPos.y << "]" << '\n';
	}

	void control(MoveType moveType)
	{
		Move move;


		if (moveType == MoveType::input)
			playerPos = move.inputStep(mapSize, playerPos);
	}

	void renderMap()
	{
		Render map;



		if (viewType == RenderType::fullMap)
			map.renderFullMap(mapSize, playerPos);

		if (viewType == RenderType::yanMoment)
			map.renderYan(mapSize, playerPos, viewSize, mapOBJ);

		if (viewType == RenderType::twoView)
			map.renderTwo(mapSize, playerPos, viewSize, mapOBJ);

		if (viewType == RenderType::inventory)
			map.inventory(inventory);
	}

	void logic()
	{
		Logic gameLogic;

		char item = gameLogic.takeItem(playerPos, mapOBJ);

		if (item != '0')
		inventory.add_items(item);

		isEnd = gameLogic.playerIsDead(playerPos, mapOBJ);
	}

	void add_items()
	{
		mapOBJ.add_stick(24, 24);
	}

	void printHpPlayer()
	{
		std::cout << mapOBJ.obj.player.actorHP.HP << "% HP" << '\n';
	}

	void setHP(int HP)
	{

		mapOBJ.obj.player.actorHP.HP = HP;

	}


};



int main()
{

	Map map;

	//Processed Frames Count
	int PFC = 0;

	//map.obj.addCookies();
	Game game(map.mapSize, map.obj.playerPos, map);

	game.setHP(1);

	game.add_items();


	while (game.isEnd == false)
	{
	
		system("cls");

		std::cout << "PFC = [" << PFC << "]" << '\n';

		game.logic();


		game.renderMap();

		game.printHpPlayer();

		game.control(MoveType::input);



		++PFC;
	}
	system("cls");
	std::cout << "You are dead!";

	return 0;
}