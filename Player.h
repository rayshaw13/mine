
#ifndef PLAYER
#define PLAYER
#include <vector>
#include <memory>
#include "MineMap.h"
#include "glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
using namespace std;

class Player
{
public:
    Player(shared_ptr<MineMap> m,GLFWwindow *w=nullptr);
    ~Player();

    int SingleLeftClick(GLFWwindow *window,double x, double y);
    int SingleLeftClick(const vector<int>& click);
    int SingleRightClick(const vector<int>& click);
    int DoubleLeftClick(const vector<int>& click);
private:
    /* data */
    GLFWwindow *m_window;
    shared_ptr<MineMap> m_mineMap;
};
#endif
