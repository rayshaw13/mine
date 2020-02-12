#include <iostream>
#include <string>
#include <sstream>
#include "MineMap.h"
#include "player.h"

int main()
{
    auto m = make_shared<MineMap>(10,10,10);
    Player pl(m);
    std::string pos;
    while (std::getline(std::cin, pos))
    {
        istringstream poss(pos);
        int x,y;
        poss>>x>>y;
        std::vector<int> click{x,y};
        int ret = pl.SingleLeftClick(click);
        m->PrintMap();
        if(ret!=0) {
            break;
        }
    }
    
    return 0;
}