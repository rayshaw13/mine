#ifndef ROLES
#define ROLES
#include "Player.h"
#include "Juger.h"
#include "display.h"
struct Roles
{
    std::shared_ptr<Player> player;
    std::shared_ptr<Juger> juger;
    std::shared_ptr<Display> displayer;
};
#endif	// ROLES