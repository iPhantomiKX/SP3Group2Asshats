#ifndef RABBIT_H
#define RABBIT_H

#include "../Monster.h"

class Monster_Rabbit : public Monster
{
public:
    Monster_Rabbit(std::string name, int stats[]) : Monster(name, stats)
    {
        m_strategy = NULL;
    }
	virtual ~Monster_Rabbit()
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
		// Do distance check between player, bait, traps
		// Do aggression change and fear change respectively
		if ((GetPosition() - player->GetPositionVector()).LengthSquared() < 8)
		{
			changeAggressionStat(5);
			changeFearStat(-5);
		}
		else if ((GetPosition() - player->GetPositionVector()).LengthSquared() > 8)
		{
			GetAggressionStat();
			GetFearStat();
		}
		if (GetHealthStat() < 40)
		{
			changeAggressionStat(-5);
			changeFearStat(5);
		}
    }

};

#endif