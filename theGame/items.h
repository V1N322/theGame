#pragma once
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
public:
	int get_HP() 
	{
		return HP; 
	}

	int get_maxHP()
	{
		return maxHP; 
	}

	int get_minHP() 
	{
		return minHP;
	}

	void set_HP(int newHP) 
	{
		HP = newHP;
	}

	void set_maxHP(int newMaxHP)
	{ 
		HP = newMaxHP;
	}
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

class Actor
{
	healthPoints HP = healthPoints(10);
	Coordinates pos = Coordinates(25, 25);

public:
	Coordinates get_pos() { return pos; }
	int get_HP() { return HP.get_HP(); }
	
	void set_pos(Coordinates newPos) { pos = newPos; }
	void set_pos(int x, int y) { pos.x = x; pos.y = y; }
};

class Stick : public Item {

	std::string name = "stick";
	char view = '-';
	healthPoints HP = healthPoints(10);

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

