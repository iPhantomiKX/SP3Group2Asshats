#ifndef MONSTER_BOSS_MUKBOSS_H
#define MONSTER_BOSS_MUKBOSS_H

#include "../Monster.h"

class Boss_MukBoss : public Monster
{
	Boss_MukBoss();
	virtual ~Boss_MukBoss();

	virtual void Update(double dt);
}

#endif