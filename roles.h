#ifndef ROLES
#define ROLES
#include "Player.h"
#include "Juger.h"
struct Roles
{
    std::shared_ptr<Player> player;
    std::shared_ptr<Juger> juger;
};
#endif	// ROLES