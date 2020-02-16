﻿#include <iostream>
#include "Juger.h"

Juger::Juger(shared_ptr<MineMap> m):mine(m)
{
}

Juger::~Juger()
{

}

int Juger::DoJuge()
{
    int cur = mine->GetHeight()*mine->GetWidth() - mine->GetRecovered();
    cout<<"recover:"<<mine->GetRecovered()<<" mines:"<<mine->GetMineNum()<<" unrecover:"<<cur<<endl;
    if(cur == mine->GetMineNum()) {
        std::cout<<"You Win"<<std::endl;
        return 1;
    }
    return 0;
}