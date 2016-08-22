#ifndef MONSTER_BOSS_MAGMA_BERZEKER_H
#define MONSTER_BOSS_MAGMA_BERZEKER_H

#include "../Monster.h"
#include "../AI_Strategy.h"

class Boss_MagmaBerzeker : public Monster
{
public:
	Boss_MagmaBerzeker()
	{
		Strategy = NULL;
	}
	virtual ~Boss_MagmaBerzeker()
	{
		if (Strategy != NULL)
		{
			delete Strategy;
			Strategy = NULL;
		}
	}

	void ChangeStrategy(AI_Strategy* newAI, bool bDelete)
	{
		if (bDelete == true)
		{
			if (Strategy != NULL)
			{
				delete Strategy;
				Strategy = NULL;
			}
		}
		Strategy = newAI;
	}

	//Monster Movement update
	virtual void Update(double dt)
	{

	}
private:
	AI_Strategy* Strategy;
};

#endif