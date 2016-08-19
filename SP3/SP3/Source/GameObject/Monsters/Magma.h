#ifndef MONSTER_MAGMA_H
#define MONSTER_MAGMA_H

#include "../Monster.h"

class Monster_Magma : public Monster
{
public:
	Monster_Magma();
	virtual ~Monster_Magma();
	
	virtual void Update(double dt);
};


#endif