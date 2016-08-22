#ifndef MONSTER_GRIMEJAM_H
#define MONSTER_GRIMEJAM_H

#include "../Monster.h"

class Monster_Grimejam : public Monster
{
public:
    Monster_Grimejam(std::string name, int stats[]) : Monster(name, stats)
	{
		m_strategy = NULL;
	}
	virtual ~Monster_Grimejam()
	{
		if (m_strategy != NULL)
		{
			delete m_strategy;
			m_strategy = NULL;
		}
	}

	void ChangeStrategy(AI_Strategy* newAI, bool bDelete)
	{
		if (bDelete == true)
		{
			if (m_strategy != NULL)
			{
				delete m_strategy;
				m_strategy = NULL;
			}
		}
		m_strategy = newAI;
	}

	//Monster Movement update
	virtual void Update(double dt)
	{

	}

};

#endif