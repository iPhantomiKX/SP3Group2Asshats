#ifndef MONSTER_RABBIT_H
#define MONSTER_RABBIT_H

#include "../Monster.h"

class Monster_Rabbit : public Monster
{
public:
	Monster_Rabbit();
	virtual ~Monster_Rabbit();

	virtual void Update(double dt);
};

#endif