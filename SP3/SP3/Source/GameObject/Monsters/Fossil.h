#ifndef MONSTER_FOSSIL_H
#define MONSTER_FOSSIL_H

#include "../Monster.h"

class Monster_Fossil : public Monster
{
public:
    Monster_Fossil(std::string name, int stats[]) : Monster(name, stats)
	{
		Strategy = NULL;
	}
	virtual ~Monster_Fossil()
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

};

#endif