#ifndef MONSTER_GOLEM_H
#define MONSTER_GOLEM_H

#include "../Monster.h"
#include "../AI_Strategy.h"

class Monster_Golem : public Monster
{
public:
	Monster_Golem()
	{
		Strategy = NULL;
	}
	virtual ~Monster_Golem()
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