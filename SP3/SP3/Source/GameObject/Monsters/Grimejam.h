#ifndef MONSTER_GRIMEJAM_H
#define MONSTER_GRIMEJAM_H

#include "../Monster.h"
#include "../AI_Strategy.h"

class Monster_Grimejam : public Monster
{
public:
	Monster_Grimejam()
	{
		Strategy = NULL;
	}
	virtual ~Monster_Grimejam()
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