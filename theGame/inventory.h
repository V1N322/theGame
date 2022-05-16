#pragma once

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