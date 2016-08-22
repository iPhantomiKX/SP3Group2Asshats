#ifndef MONSTER_BOSS_MUKBOSS_H
#define MONSTER_BOSS_MUKBOSS_H

#include "../Monster.h"
#include "../AI_Strategy.h"

class Boss_MukBoss : public Monster
{
public:
	Boss_MukBoss()
	{
		Strategy = NULL;
	}
	virtual ~Boss_MukBoss()
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
}

#endif