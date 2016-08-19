#ifndef MONSTER_BOSS_FAIRY_H
#define MONSTER_BOSS_FAIRY_H

#include "../Monster.h"

class Boss_Fairy : public Monster
{
public:
	Boss_Fairy();
	virtual ~Boss_Fairy();

	virtual void Update(double dt);
};


#endif 