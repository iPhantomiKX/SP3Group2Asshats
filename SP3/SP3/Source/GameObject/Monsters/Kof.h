#ifndef MONSTER_KOF_H
#define MONSTER_KOF_H

#include "../Monster.h"
#include "../AI_Strategy.h"

class Monster_Kof : public Monster
{
public:
	Monster_Kof()
	{
		Strategy = NULL;
	}
	virtual ~Monster_Kof()
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