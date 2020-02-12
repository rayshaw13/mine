
#ifndef PLAYER
#define PLAYER
#include <vector>
#include <memory>
#include "MineMap.h"
using namespace std;

class Player
{
private:
    /* data */
    shared_ptr<MineMap> mine;
public:
    Player(shared_ptr<MineMap> m);
    ~Player();

    int SingleLeftClick(const vector<int>& click);
    int SingleRightClick(const vector<int>& click);
    int DoubleLeftClick(const vector<int>& click);

};
#endif
