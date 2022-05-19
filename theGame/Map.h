#pragma once

#include "items.h"

#include <list>
#include <memory>


class Map {
    std::list<std::shared_ptr<Item>> items;
    Actor player;
    Coordinates mapSize = Coordinates(50, 50);

public:
    Map()
    {
    }


    Coordinates get_mapSize()
    {
        return mapSize;
    }

    Actor get_actor()
    {
        return player;
    }

    std::string get_name(int numItem)
    {
        int num = 0;

        std::string result = "NONE";

        for (const auto& item : items) {
            if (num == numItem) {
                result = item->get_name();
                break;
            }
            ++num;
        }

        return result;
    }

    const std::list<std::shared_ptr<Item>>& get_items()
    {
        return items;
    }

    void clear_items()
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

    char stepOnItem(Coordinates playerPos)
    {

        for (auto it = items.begin(); it != items.end(); ++it) {

            if ((*it)->get_pos().x == playerPos.x && (*it)->get_pos().y == playerPos.y) {
                char symbol = (*it)->get_view();
                deleteItem(playerPos);
                return symbol;
            }
        }
        return '0';
    }
};
