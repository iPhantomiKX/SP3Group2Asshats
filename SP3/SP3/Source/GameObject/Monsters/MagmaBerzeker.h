#ifndef MONSTER_BOSS_MAGMA_BERZEKER_H
#define MONSTER_BOSS_MAGMA_BERZEKER_H

#include "../Monster.h"

class Boss_MagmaBerzeker : public Monster
{
public:
	Boss_MagmaBerzeker();
	virtual ~Boss_MagmaBerzeker();

	virtual void Update(double dt);
};

#endif