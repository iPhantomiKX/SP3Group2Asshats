#ifndef MONSTER_BOSS_ROCKSNAKE_H
#define MONSTER_BOSS_ROCKSNAKE_H

#include "../Monster.h"

class Boss_RockSnake : public Monster
{
public:
	Boss_RockSnake();
	virtual ~Boss_RockSnake();

	virtual void Update(double dt);
};



#endif