#include "theGame.h"

class Actor
{
  Coordinates actorPos = Coordinates(25, 25);

public:
	Coordinates get_actorPos() { return actorPos;}
};

class OBJ
{
public:
  Actor player;
  Coordinates playerPos = player.get_actorPos();

	std::list<Coordinates> cookies = { Coordinates(26, 26), Coordinates(23, 24), Coordinates(22, 23), Coordinates(23, 25)};

public:
	Coordinates get_playerPos()
	{
		return playerPos;
	}

	std::list<Coordinates> get_cookiesPos()
	{
		return cookies;
	}
};

class Map
{
public:
	Coordinates mapSize = Coordinates(50, 50);

	OBJ obj;

};




enum class MoveType
{
	oneStep,
	input
};

enum class RenderType
{
	fullMap,
	yanMoment,
	twoView
};

RenderType viewType = RenderType::fullMap;

void changeView()
{
	if (viewType == RenderType::fullMap)
		viewType = RenderType::yanMoment;

	else if (viewType == RenderType::yanMoment)
		viewType = RenderType::twoView;

	else if (viewType == RenderType::twoView)
		viewType = RenderType::fullMap;
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

		for(int b = 0; b != mapSize.y; b++){

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

	void buildYan(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> cookies, int viewSize)
	{
		
		for (int y = viewSize - viewSize*2; y != viewSize + 1; ++y)
		{
		  for (int x = -viewSize; x != viewSize + 1; ++x)
		  {
				int X = x + playerPos.x;
				int Y = y + playerPos.y;
	

				std::cout << " ";


				bool hasCookies = false;

				for (Coordinates n : cookies)
				{
					if (X == n.x && Y == n.y){
						hasCookies = true;
						break;
					}
				}

				if (X == playerPos.x && Y == playerPos.y)
					std::cout << 'P';

				else if (hasCookies)
					std::cout << "•";

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
	void renderFullMap(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> cookies)
	{

		buildUpFull(mapSize);

		buildBaseFull(mapSize, playerPos, cookies);

		buildDownFull(mapSize);
	}

	void renderYan(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> cookies, int viewSize)
	{
		buildYan(mapSize, playerPos, cookies, viewSize);

	}

	void renderTwo(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> cookies, int viewSize)
	{
		renderYan(mapSize, playerPos, cookies, viewSize);
		renderFullMap(mapSize, playerPos, cookies);
	}
};



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

		if (buttonPressed == 'w'){
			--newPos.y;
			if (newPos.y == -1)
				++newPos.y;
		}
		if (buttonPressed == 'a')	
		{
			--newPos.x;
			if (newPos.x == -1)
				++newPos.x;
		}

		if (buttonPressed == 's')
		{
			++newPos.y;
			if (newPos.y == mapSize.y)
				--newPos.y;
			}

		if (buttonPressed == 'd')
		{
			++newPos.x;
			if (newPos.x == mapSize.x)
				--newPos.x;
		}

		if (buttonPressed == 'n')
		{
			changeView();
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
		}

		return resultList;
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

	Game(const Coordinates& aMapSize, const Coordinates& aPlayerPos, const std::list<Coordinates>& aCookies)
		:mapSize(aMapSize), playerPos(aPlayerPos), cookies(aCookies)
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
			map.renderYan(mapSize, playerPos, cookies, viewSize);

		if (viewType == RenderType::twoView)
			map.renderTwo(mapSize, playerPos, cookies, viewSize);
	}

	void logic()
	{
		Logic gameLogic;

		cookies = gameLogic.eatCookies(cookies, playerPos);


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
		std::cout << "Eaten cookies = " << eatCookies << std::endl;
	}

};



int main()
{

	Map map;

	//Processed Frames Count
	int PFC = 0;

	Game game(map.mapSize, map.obj.get_playerPos(), map.obj.get_cookiesPos());

	while (true)
	{
		system("cls");

		std::cout << "PFC = [" << PFC << "]" << std::endl;
		game.logic();
		game.printNumberOfCookies();
		game.eatenCookies();
		game.renderMap();
		game.showPosPlayer();
		game.control(MoveType::input);
		
		
	
		++PFC;
	}

	return 0;
}