#ifndef MONSTER_GOLEM_H
#define MONSTER_GOLEM_H

#include "../Monster.h"

class Monster_Golem : public Monster
{
	Monster_Golem();
	virtual ~Monster_Golem();

	virtual void Update(double dt);
};

#endif