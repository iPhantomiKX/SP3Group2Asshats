#ifndef MONSTER_KOF_H
#define MONSTER_KOF_H

#include "../Monster.h"

class Monster_Kof : public Monster
{
public:
	Monster_Kof();
	virtual ~Monster_Kof();

	virtual void Update(double dt);
};

#endif