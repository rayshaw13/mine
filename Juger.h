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
public:
    Juger(shared_ptr<MineMap> m);
    ~Juger();

    int DoJuge();
};

#endif
