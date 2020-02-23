#include "Player.h"
#include <iostream>

Player::Player(shared_ptr<MineMap> m): mine(m)
{
}

Player::~Player()
{
}


int Player::SingleLeftClick(const vector<int>& click)
{
    int ret = mine->RecoverOnClick(click);
    if(ret==-1) {
        std::cout<<"You are blown up!"<<endl;
        mine->PrintMapAll();
        return -1;
    }
    mine->PrintMap();
    return ret;
}
int Player::SingleRightClick(const vector<int>& click)
{
// to do
    return 0;
}
int Player::DoubleLeftClick(const vector<int>& click)
{
// to do
    return 0;
}
