#pragma once


	void renderYan(int viewSize, Map map)
	{
		Coordinates mapSize = map.get_mapSize();
		Actor actor = map.get_actor();
		Coordinates playerPos = actor.get_pos();

		for (int y = viewSize - viewSize * 2; y != viewSize + 1; ++y)
		{
			for (int x = -viewSize; x != viewSize + 1; ++x)
			{
				int X = x + playerPos.x;
				int Y = y + playerPos.y;

				auto& items = map.get_items();

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




