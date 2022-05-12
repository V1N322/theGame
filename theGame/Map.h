#pragma once

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


class Item {
Coordinates pos;

protected:
	Coordinates itemPos()
	{
		return pos;
	}

public:
    Item(int x, int y)
        : pos(x, y)
        
    {

    }

	Item()
		: pos(0, 0)
	{

	}

    virtual ~Item()
    {
		
    }

	virtual Coordinates get_pos() = 0;

	virtual std::string get_name() = 0;

	virtual char get_view() = 0;
};

class Stick : public Item {

	std::string name = "stick";
	char view;

public:
    Stick(Coordinates pos)
        : Item(pos.x, pos.y)
    {
    }
	Stick(int x, int y)
		: Item(x, y)
	{
	}
	Stick()
	{
	}
	
	
	Coordinates get_pos()
	{
		return itemPos();
	}

	std::string get_name()
	{
		return name;
	}
	
	char get_view()
	{
		return view;
	}

};




class OBJ
{
public:

	Actor player;
	Coordinates playerPos = player.get_actorPos();

};

class Map
{
	std::list<std::shared_ptr<Item>> items;

public:
	Map()
	{
	}


	Coordinates mapSize = Coordinates(50, 50);

	OBJ obj;

	void add_stick(int x, int y)
	{
		items.push_back(std::make_shared<Stick>(x, y));
	}

	std::string get_name(int numItem)
	{
		int num = 0;

		std::string result = "NONE";

		for (const auto& item : items)
		{
			if (num == numItem) {
				result = item->get_name();
				break;
			}
			++num;
		}
		
		return result;
	}

	std::list<std::shared_ptr<Item>> get_items()
	{
		return items;
	}

	std::list<std::shared_ptr<Item>> clear_items()
	{
		items.clear();
	}

	void deleteItem(const Coordinates& playerPos)
	{
		for (auto it = items.begin(); it != items.end(); ++it) {
			if ((*it)->get_pos().x == playerPos.x && (*it)->get_pos().y == playerPos.y) {
				items.erase(it);
			}
		}
	}

	char takeItem(Coordinates playerPos)
	{

		for (auto it = items.begin(); it != items.end(); ++it) {

			if ((*it)->get_pos().x == playerPos.y && (*it)->get_pos().x == playerPos.y)
			{
				char symbol =  (*it)->get_view();
				deleteItem(playerPos);
				return symbol;
			}
			return '0';
		}
	}
	
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