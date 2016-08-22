#ifndef MONSTER_GOLEM_H
#define MONSTER_GOLEM_H

#include "../Monster.h"

class Monster_Golem : public Monster
{
public:
    Monster_Golem(std::string name, int stats[]) : Monster(name, stats)
	{
		m_strategy = NULL;
	}
	virtual ~Monster_Golem()
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