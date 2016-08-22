#ifndef MONSTER_BIRD_H
#define MONSTER_BIRD_H

#include "../Monster.h"


class Monster_Bird : public Monster
{
public:
	Monster_Bird()
	{
		Strategy = NULL;
	}
	virtual ~Monster_Bird()
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