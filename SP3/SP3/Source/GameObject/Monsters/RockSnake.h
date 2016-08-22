#ifndef MONSTER_BOSS_ROCKSNAKE_H
#define MONSTER_BOSS_ROCKSNAKE_H

#include "../Monster.h"
#include "../AI_Strategy.h"

class Boss_RockSnake : public Monster
{
public:
	Boss_RockSnake()
	{
		Strategy = NULL;
	}
	virtual ~Boss_RockSnake()
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