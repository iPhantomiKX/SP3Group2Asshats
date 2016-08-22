#ifndef MONSTER_KOF_H
#define MONSTER_KOF_H

#include "../Monster.h"

class Monster_Kof : public Monster
{
public:
    Monster_Kof(std::string name, int stats[]) : Monster(name, stats)
	{
		m_strategy = NULL;
	}
	virtual ~Monster_Kof()
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