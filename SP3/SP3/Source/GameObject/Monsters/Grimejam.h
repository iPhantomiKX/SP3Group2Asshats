#ifndef MONSTER_GRIMEJAM_H
#define MONSTER_GRIMEJAM_H

#include "../Monster.h"

class Monster_Grimejam : public Monster
{
public:
	Monster_Grimejam();
	virtual ~Monster_Grimejam();

	virtual void Update(double dt);
};

#endif