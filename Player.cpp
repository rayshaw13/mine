#include "Player.h"
#include <iostream>


Player::Player(shared_ptr<MineMap> m, GLFWwindow *w) : m_window(w), m_mineMap(m)
{
}

Player::~Player()
{
}

int Player::SingleLeftClick(GLFWwindow *window, double x, double y)
{
    // find position
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    int rows = m_mineMap->GetRows();
    int colums = m_mineMap->GetColums();
    int rindex = int(x/width*rows);
    int cindex = int(y/height*colums);
    std::cout<<"width:"<<width<<" rows:"<<rows<<" "<<x<<" "<<int(x/width*rows)<< std::endl;
    std::cout<<"height:"<<height<<" cols:"<<colums<<" "<<y<<" "<<int(y/height*colums)<< std::endl;
    vector<int> click{cindex,rindex};
    return SingleLeftClick(click);
}

int Player::SingleLeftClick(const vector<int> &click)
{
    int ret = m_mineMap->RecoverOnClick(click);
    if (ret == -1)
    {
        std::cout << "You are blown up!" << endl;
        m_mineMap->PrintMapAll();
        return -1;
    }
    m_mineMap->PrintMap();
    return ret;
}
int Player::SingleRightClick(const vector<int> &click)
{
    // to do
    return 0;
}
int Player::DoubleLeftClick(const vector<int> &click)
{
    // to do
    return 0;
}
