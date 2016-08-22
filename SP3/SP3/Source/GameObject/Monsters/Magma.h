#ifndef MONSTER_MAGMA_H
#define MONSTER_MAGMA_H

#include "../Monster.h"
#include "../AI_Strategy.h"

class Monster_Magma : public Monster
{
public:
	Monster_Magma()
	{
		Strategy = NULL;
	}
	virtual ~Monster_Magma()
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