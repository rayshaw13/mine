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
    int cindex = int(x/width*colums);
    int rindex = int(y/height*rows);
    std::cout<<"height:"<<height<<" rows:"<<rows<<" "<<y<<" "<<rindex<< std::endl;
    std::cout<<"width:"<<width<<" cols:"<<colums<<" "<<x<<" "<<cindex<< std::endl;
    vector<int> click{rindex,cindex};
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
