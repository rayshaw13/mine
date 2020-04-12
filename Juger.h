#ifndef JUGER
#define JUGER
#include <memory>
#include "MineMap.h"
using namespace std;

class Juger
{
private:
    shared_ptr<MineMap> mine;
    int lastmine;
    int m_win;
public:
    Juger(shared_ptr<MineMap> m);
    ~Juger();

    int DoJuge();
    int GetGameState();
};

#endif
