#ifndef MONSTER_RABBIT_H
#define MONSTER_RABBIT_H

#include "../Monster.h"
#include "../AI_Strategy.h"

class Monster_Rabbit : public Monster
{
public:
	Monster_Rabbit()
	{
		Strategy = NULL;
	}
	virtual ~Monster_Rabbit()
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