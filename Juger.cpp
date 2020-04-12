#include <iostream>
#include "Juger.h"

Juger::Juger(shared_ptr<MineMap> m):mine(m)
{
}

Juger::~Juger()
{

}

int Juger::DoJuge()
{
    if(mine->IsBloomed()) {
        m_win = -1;
    }
    int cur = mine->GetRows()*mine->GetColums() - mine->GetRecovered();
    std::cout<<"recover:"<<mine->GetRecovered()<<" mines:"<<mine->GetMineNum()<<" unrecover:"<<cur<<std::endl;
    if(cur == mine->GetMineNum()) {
        std::cout<<"You Win"<<std::endl;
        m_win = 1;
        return 1;
    }
    return 0;
}

Juger::GetGameState()
{
    return m_win;
}