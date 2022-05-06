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
		std::cout << std::endl;
	}

	void buildBaseFull(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> cookies)
	{

		for (int b = 0; b != mapSize.y; b++) {

			std::cout << '*';

			for (int i = 0; i != mapSize.x; ++i)
			{
				bool cellhasCookies = false;
				for (Coordinates n : cookies) {
					if (n.x == i && n.y == b)
					{
						if (n.x == playerPos.x &&
							n.y == playerPos.y)
							1 + 2;
						else
							std::cout << '0';

						cellhasCookies = true;
					}
				}


				if (b == playerPos.y && i == playerPos.x) {

					std::cout << 'P';

				}



				else {
					if (cellhasCookies == false)
						std::cout << ' ';

				}




				std::cout << ' ';

			}
			std::cout << '*';

			std::cout << std::endl;
		}

	}

	void buildDownFull(Coordinates mapSize)
	{
		for (int i = -2; i != mapSize.x * 2; ++i)
			std::cout << '*';
		std::cout << std::endl;
	}

public:

	void buildYan(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> cookies, int viewSize, Map obj)
	{
		std::list<Coordinates>thornsPos = obj.obj.thorns.get_thornsPos();

		for (int y = viewSize - viewSize * 2; y != viewSize + 1; ++y)
		{
			for (int x = -viewSize; x != viewSize + 1; ++x)
			{
				int X = x + playerPos.x;
				int Y = y + playerPos.y;


				std::cout << " ";


				bool hasCookies = false;
				bool hasThorns = false;

				for (Coordinates n : thornsPos)
				{
					if (X == n.x && Y == n.y)
					{
						hasThorns = true;
						break;
					}
				}

				for (Coordinates n : cookies)
				{
					if (X == n.x && Y == n.y) {
						hasCookies = true;
						break;
					}
				}

				if (X == playerPos.x && Y == playerPos.y)
					std::cout << 'P';

				else if (hasCookies)
					std::cout << "X";

				else if (hasThorns)
					std::cout << "*";

				else if (X == obj.obj.frogPos.x && Y == obj.obj.frogPos.y)
					std::cout << obj.obj.viewFrog;

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
	void renderFullMap(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> cookies)
	{

		buildUpFull(mapSize);

		buildBaseFull(mapSize, playerPos, cookies);

		buildDownFull(mapSize);
	}

	void renderYan(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> cookies, int viewSize, Map obj)
	{
		buildYan(mapSize, playerPos, cookies, viewSize, obj);

	}

	void renderTwo(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> cookies, int viewSize, Map obj)
	{
		renderYan(mapSize, playerPos, cookies, viewSize, obj);
		renderFullMap(mapSize, playerPos, cookies);
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
		Coordinates newPos(playerPos.x, playerPos.y);

		Button button;

		char buttonPressed = button.isPressed();

		if (buttonPressed == 'w' && viewType != RenderType::inventory) {
			--newPos.y;
			if (newPos.y == -1)
				++newPos.y;
		}
		if (buttonPressed == 'a' && viewType != RenderType::inventory)
		{
			--newPos.x;
			if (newPos.x == -1)
				++newPos.x;
		}

		if (buttonPressed == 's' && viewType != RenderType::inventory)
		{
			++newPos.y;
			if (newPos.y == mapSize.y)
				--newPos.y;
		}

		if (buttonPressed == 'd' && viewType != RenderType::inventory)
		{
			++newPos.x;
			if (newPos.x == mapSize.x)
				--newPos.x;
		}

		if (buttonPressed == 'n')
		{
			changeView();
		}

		if (buttonPressed == 'v')
		{
			changeView('v');
		}

		return newPos;
	}
};

class Logic
{
public:
	std::list<Coordinates> eatCookies(std::list<Coordinates> listCookies, Coordinates playerPos)
	{
		std::list<Coordinates> resultList;

		for (Coordinates n : listCookies)
		{
			if (n.x != playerPos.x || n.y != playerPos.y)
			{
				resultList.push_back(n);
			}
			else
				std::cout << "You are eaten cookies and restored One hit point" << '\n';
		}

		return resultList;
	}

	int stepOnThorns(Coordinates playerPos, Map obj)
	{
		int hp = obj.obj.player.actorHP.HP;

		for (Coordinates n : obj.obj.thorns.get_thornsPos())
		{
			if (n.x == playerPos.x && n.y == playerPos.y)
			{
				hp = hp - obj.obj.thorns.get_thornsDamage();
			}
		}
		return hp;
	}

	Coordinates frogJump(Map obj)
	{
		


			if (frogJumpInt != 3)
			{
				if (frogJumpInt == 0)
				{
					
					obj.obj.frogPos.y = --obj.obj.frogPos.y;
				}

				else if (frogJumpInt == 1)
				{
					obj.obj.frogPos.y = ++obj.obj.frogPos.y;
				}


				++frogJumpInt;
			}

			if (frogJumpInt == 2)
				frogJumpInt = 0;
			
		
		return obj.obj.frogPos;
		
	}
	
	Inventory takeFrog(Map obj, Coordinates playerPos, Inventory inventory)
	{
		if (obj.obj.frogPos.y == playerPos.y && obj.obj.frogPos.x == playerPos.x)
		{
			inventory.add_items('8');
		}
		return inventory;
	}
	
	Coordinates hideFrog(Map obj, Coordinates playerPos)
	{
		if (obj.obj.frogPos.y == playerPos.y && obj.obj.frogPos.x == playerPos.x)
		{
			obj.obj.frogPos.x = -1000;
			obj.obj.frogPos.y = -1000;
		}
		return obj.obj.frogPos;
	}

	bool playerIsDead(Coordinates playerPos, Map obj)
	{
		if (obj.obj.player.actorHP.HP != obj.obj.player.actorHP.minHP)
			return false;
		if (obj.obj.player.actorHP.HP <= obj.obj.player.actorHP.minHP)
			return true;

		return false;
	}

};

class Game
{
public:
	Coordinates mapSize;
	Coordinates playerPos;
	std::list<Coordinates> cookies;
	int viewSize = 6;
	int numberCookies = cookies.size();
	int eatCookies = 0;
	int healthReplenished = 0;
	bool isEnd = false;
	Inventory inventory;
	Map objects;

	

	Game(const Coordinates& aMapSize, const Coordinates& aPlayerPos, const std::list<Coordinates>& aCookies, const Map& aObjects)
		:mapSize(aMapSize), playerPos(aPlayerPos), cookies(aCookies), objects(aObjects)
	{
		mapSize = aMapSize;
		playerPos = aPlayerPos;
		cookies = aCookies;
	}


public:
	void showPosPlayer()
	{
		std::cout << "the player is on " << "[X = " << playerPos.x << ", Y = " << playerPos.y << "]" << std::endl;
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
			map.renderFullMap(mapSize, playerPos, cookies);

		if (viewType == RenderType::yanMoment)
			map.renderYan(mapSize, playerPos, cookies, viewSize, objects);

		if (viewType == RenderType::twoView)
			map.renderTwo(mapSize, playerPos, cookies, viewSize, objects);

		if (viewType == RenderType::inventory)
			map.inventory(inventory);
	}

	void logic()
	{
		Logic gameLogic;

		cookies = gameLogic.eatCookies(cookies, playerPos);

		objects.obj.player.actorHP.HP = gameLogic.stepOnThorns(playerPos, objects);

		objects.obj.frogPos = gameLogic.frogJump(objects);

		inventory = gameLogic.takeFrog(objects, playerPos, inventory);

		objects.obj.frogPos = gameLogic.hideFrog(objects, playerPos);

		isEnd = gameLogic.playerIsDead(playerPos, objects);
	}

	void printNumberOfCookies()
	{
		std::cout << "Number of cookies = " << cookies.size() << std::endl;
	}

	void eatenCookies()
	{
		if (numberCookies != cookies.size())
		{
			eatCookies = numberCookies - cookies.size();
		}
	}

	void printHpPlayer()
	{
		std::cout << objects.obj.player.actorHP.HP << "% HP" << std::endl;
	}

	void setHP(int HP)
	{

		objects.obj.player.actorHP.HP = HP;

	}

	void cookieCure(int HP)
	{
		if (eatCookies != healthReplenished)
		{
			objects.obj.player.actorHP.HP = objects.obj.player.actorHP.HP + HP;
			++healthReplenished;

			if (objects.obj.player.actorHP.HP > objects.obj.player.actorHP.maxHP)
			{
				objects.obj.player.actorHP.HP = objects.obj.player.actorHP.HP - HP;
			}
		}
	}

};

void start()
{

	Map map;

	//Processed Frames Count
	int PFC = 0;

	//map.obj.addCookies();
	Game game(map.mapSize, map.obj.get_playerPos(), map.obj.get_cookiesPos(), map);
	
	game.setHP(1);

	while (game.isEnd == false)
	{
		system("cls");

		std::cout << "PFC = [" << PFC << "]" << std::endl;
		game.eatenCookies();
		game.cookieCure(1);

		game.logic();

		game.renderMap();

		game.printHpPlayer();

		game.control(MoveType::input);



		++PFC;
	}
	system("cls");
	std::cout << "You are dead!";

}

int main()
{

	start();

	return 0;
}