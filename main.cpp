#include <iostream>
#include <string>
#include <sstream>
#include "MineMap.h"
#include "player.h"
#include "Juger.h"
#include <locale.h>

int main()
{
    setlocale(LC_CTYPE,"");
    int height,width,num;
    std::cout<<"Plz input minemap's height:";
    std::cin>>height;
    std::cout<<"Plz input minemap's width:";
    std::cin>>width;
    std::cout<<"Plz input mine number:";
    std::cin>>num;
    auto m = make_shared<MineMap>(height,width,num);
    std::cin.clear();
    std::cin.sync();
    // std::cin.ignore();
    Player pl(m);
    Juger jl(m);
    std::string pos;
    while (std::getline(std::cin, pos))
    {
        if(!pos.empty()&&tolower(pos.front())=='q'){
            break;
        }
        std::cout<<"You Clicked the Position:"<<pos<<std::endl;
        istringstream poss(pos);
        int x,y;
        poss>>x>>y;
        std::vector<int> click{x,y};
        int ret = pl.SingleLeftClick(click);
        if(ret==-1) {
            break;
        }
        ret = jl.DoJuge();
        if(ret == 1) {
            break;
        }
    }
    getchar();
    
    return 0;
}