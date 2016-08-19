#ifndef MONSTER_FOSSIL_H
#define MONSTER_FOSSIL_H

#include "../Monster.h"

class Monster_Fossil : public Monster
{
	Monster_Fossil();
	virtual ~Monster_Fossil();

	virtual void Update(double dt);
};

#endif