#pragma once
#include "theGame.h"

int randInt(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	static std::default_random_engine engine;
	return distribution(engine);
}

struct healthPoints
{
	int HP;
	int maxHP;
	int minHP;

	healthPoints(int hp)
	{
		HP = hp;
		maxHP = HP;
		minHP = 0;
	}

};

class Actor
{
	Coordinates actorPos = Coordinates(25, 25);

public:
	healthPoints actorHP = healthPoints(10);

public:
	int get_HP() { return actorHP.HP; }
	int get_maxHP() { return actorHP.maxHP; }
	int get_minHP() { return actorHP.minHP; }
	Coordinates get_actorPos() { return actorPos; }

};

class Thorn
{
	int damage = 1;
	std::list<Coordinates> ThornsPos = {Coordinates(24, 24)};

public:
	std::list<Coordinates> get_thornsPos()
	{
		return ThornsPos;
	}
	int get_thornsDamage()
	{
		return damage;
	}
};

class Frog
{
	char view = '8';
	Coordinates frogPos;
	int jump = 0;


public:
	Coordinates get_frogPos()
	{
		return frogPos;
	}

	char viewFrog()
	{
		return view;
	}

	int jumpEd()
	{
		return jump;
	}
};	

class Stick
{

public:
	Stick();

	Coordinates pos;
	char view = '-';
	std::string name = "Stick";

};

class Items
{
	std::list<Stick> sticks; 
	
public:
	void add_stick(Coordinates pos, char symbol, std::string name)
	{ 
		Stick stick;

		stick.pos = pos;
		stick.view = symbol;
		stick.name = name;
		sticks.push_back(stick);
	}

	std::list<Stick> get_sticks()
	{

		return sticks;
	}

	Coordinates get_posStick(int numStick)
	{
		int num = 0;
		for (Stick n : sticks)
		{
			if (num > numStick)
			{
				if (num == numStick)
					return n.pos;
				++num;
			}
				
		}
		return Coordinates(0, 0);
	}

	char get_viewStick(int numStick)
	{
		int num = 0;
		for (Stick n : sticks)
		{
			if (num > numStick)
			{
				if (num == numStick)
					return n.view;
				++num;
			}
		}
		return '-';
	}

	std::string get_name(int numStick)
	{
		int num = 0;
		for (Stick n : sticks)
		{
			if (num > numStick)
			{
				if (num == numStick)
					return n.name;
				++num;
			}
				
		}
		return "Stick";
	}

	void set_stickPos(int numStick, Coordinates pos)
	{

		std::list<Stick> resultList;
		int num = 0;
		for (Stick n : sticks)
		{
			if (num == numStick)
			{
				n.pos = pos;
				resultList.push_back(n);
			}
			resultList.push_back(n);
			++num;
		}
	}
};

class OBJ
{
public:
	
	Actor player;
	Thorn thorns;
	Frog frog;
	Coordinates frogPos = frog.get_frogPos();
	char viewFrog = frog.viewFrog();
	int frogJump = frog.jumpEd();
	Coordinates playerPos = player.get_actorPos();
	int numberOfCookies = randInt(10, 30);
	std::list<Coordinates> thornsPos = thorns.get_thornsPos();
	int thornsDamage = thorns.get_thornsDamage();

	std::list<Coordinates> cookies = { Coordinates(26, 26), Coordinates(23, 24), Coordinates(22, 23), Coordinates(23, 25) };


	void addCookies() {

		while (numberOfCookies != 0)
		{
			cookies.push_back(Coordinates(randInt(0, 50), randInt(0, 50)));
			--numberOfCookies;
		}
	}

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
	Map();

	Coordinates mapSize = Coordinates(50, 50);

	OBJ obj;

	Items item;
};

class Inventory
{
public:

	std::list<char> items = {  };
	int sizeInventory = 3;

	std::list<char> get_items()
	{
		return items;
	}

	void add_items(char item)
	{
		items.push_back(item);
	}

	int get_invrntorySize()
	{
		return sizeInventory;
	}

	void set_invrntorySize(int size)
	{
		sizeInventory = size;
	}
};