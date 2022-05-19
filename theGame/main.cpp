#include "theGame.h"


int main()
{
    int PFC = 0;

    Game map_one;
    Controller control(map_one);

    map_one.create_map(Coordinates(10, 10));

    //	map_one.add_player(PlayerState); //пока не уверен в том, что здесь будет
    //	map_one.set_playerStartPos(x, y);
    //	map_one.add_item(Stick(x, y));
    //	map_one.add_wall(StoneMaterial, Coordinates(x, y));
    //	map_one.add_field(StoneMaterial, Coordinates(x, y), Coordinates(x, y));


    control.start();


    return 0;
}
