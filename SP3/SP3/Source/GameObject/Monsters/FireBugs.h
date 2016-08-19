#ifndef MONSTER_FIRE_BUGS_H
#define MONSTER_FIRE_BUGS_H

#include "../Monster.h"

class Monster_FireBugs : public Monster
{
public:
	Monster_FireBugs();
	virtual ~Monster_FireBugs();

	virtual void Update(double dt);
};

#endif