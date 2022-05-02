#include "theGame.h"

class Actor
{
  Coordinates actorPos = Coordinates(5, 5);

public:
	Coordinates get_actorPos() { return actorPos;}
};

class OBJ
{
public:
  Actor player;
  Coordinates playerPos = player.get_actorPos();

	Coordinates cookes_1 = Coordinates(6, 6);
	Coordinates cookes_2 = Coordinates(3, 4);
	Coordinates cookes_3 = Coordinates(2, 3);



	std::list<Coordinates> cookes = {cookes_1, cookes_2, cookes_3};

public:
	Coordinates get_playerPos()
	{
		return playerPos;
	}

	std::list<Coordinates> get_cookesPos()
	{
		return cookes;
	}
};

class Map
{
public:
	Coordinates mapSize = Coordinates(10, 10);

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

	void buildBaseFull(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> coockes)
	{

		for(int b = 0; b != mapSize.y; b++){

			std::cout << '*';

			for (int i = 0; i != mapSize.x; ++i)
			{
				bool cellhasCookes = false;
				for (Coordinates n : coockes) {
					if (n.x == i && n.y == b)
					{
									if (n.x == playerPos.x &&
										n.y == playerPos.y)
									  1 + 2;
						else
							std::cout << '0';
						
						cellhasCookes = true;
					}
				}
				
				
				if (b == playerPos.y && i == playerPos.x) {

					std::cout << 'P';

				}

					

				else {
					if (cellhasCookes == false)
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

	void buildYan(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> coockes, int viewSize)
	{
		
		for (int y = viewSize - viewSize*2; y != viewSize + 1; ++y)
		{
		  for (int x = -viewSize; x != viewSize + 1; ++x)
		  {
				int X = x + playerPos.x;
				int Y = y + playerPos.y;
	

				std::cout << " ";


				//std::cout << "x = " << X << ", y = " << Y;

				bool hasCookies = false;

				for (Coordinates n : coockes)
				{
					if (X == n.x && Y == n.y){
						hasCookies = true;
						break;
					}
				}

				if (X == playerPos.x && Y == playerPos.y)
					std::cout << 'P';

				else if (hasCookies)
					std::cout << '•';

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
	void renderFullMap(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> coockes)
	{

		buildUpFull(mapSize);

		buildBaseFull(mapSize, playerPos, coockes);

		buildDownFull(mapSize);
	}

	void renderYan(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> coockes, int viewSize)
	{
		buildYan(mapSize, playerPos, coockes, viewSize);

	}

	void renderTwo(Coordinates mapSize, Coordinates playerPos, std::list<Coordinates> coockes, int viewSize)
	{
		renderYan(mapSize, playerPos, coockes, viewSize);
		renderFullMap(mapSize, playerPos, coockes);
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

		if (playerPos.x != 1 || playerPos.y != 1 || playerPos.x != mapSize.x || playerPos.y != mapSize.y)
		{


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
			
		}

		

		return newPos;
	}
};

//Changes!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class Logic
{
public:
	std::list<Coordinates> eatCookies(std::list<Coordinates> listCookies, Coordinates playerPos)
	{
		std::list<Coordinates> resultList;

		for (Coordinates n : listCookies)
		{
			if (n.x != playerPos.x && n.y != playerPos.y)
			{
				resultList.push_back(n);
			}
		}

		return resultList;
	}
};
//Changes!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

class Game
{
public:
	Coordinates mapSize;
	Coordinates playerPos;
	std::list<Coordinates> coockes;
	int viewSize = 10;

	//Конструктор
	Game(const Coordinates& aMapSize, const Coordinates& aPlayerPos, const std::list<Coordinates>& aCoockes)
		:mapSize(aMapSize), playerPos(aPlayerPos), coockes(aCoockes)
	{
		mapSize = aMapSize;
		playerPos = aPlayerPos;
		coockes = aCoockes;
	}
	//Конструктор


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
			map.renderFullMap(mapSize, playerPos, coockes);

		if (viewType == RenderType::yanMoment)
			map.renderYan(mapSize, playerPos, coockes, viewSize);

		if (viewType == RenderType::twoView)
			map.renderTwo(mapSize, playerPos, coockes, viewSize);
	}
	//Changes!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	void logic()
	{
		Logic gameLogic;

		coockes = gameLogic.eatCookies(coockes, playerPos);

		
	}
	//Changes!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
};



int main()
{

	Map map;

	//Processed Frames Count
	int PFC = 0;

	Game game(map.mapSize, map.obj.get_playerPos(), map.obj.get_cookesPos());

	while (true)
	{
		system("cls");

		std::cout << "PFC = [" << PFC << "]" << std::endl;

		game.logic();
		game.renderMap();
		game.showPosPlayer();
		game.control(MoveType::input);
		
		
	
		++PFC;
	}

	return 0;
}