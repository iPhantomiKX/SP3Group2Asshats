/******************************************************************************/
/*!
\file	AI_Strategy.cpp
\author Muhammad Amirul Bin Zaol-kefli
\par	email: 150509T@mymail.nyp.edu.sg
\brief
Class that Updates the strategy of monster
*/
/******************************************************************************/
#include "AI_Strategy.h"
#include "Monster.h"

AI_Strategy::AI_Strategy()
{
}
AI_Strategy::~AI_Strategy()
{
}

AI_Strategy::STRATEGY_MODE AI_Strategy::GetCurrentStrategy()
{
	return currentState;
}
void AI_Strategy::SetState(AI_Strategy::STRATEGY_MODE currentState)
{
	this->currentState = currentState;
}

int AI_Strategy::CalculateDistance(const Vector3& MonsterPos, const Vector3& Destination)
{
	return int((Destination - MonsterPos).LengthSquared());
}

void AI_Strategy::Update()
{
	float m_aggressionLevel = monster->GetAggressionStat();
	float m_fearLevel = monster->GetFearStat();
    
	if (m_aggressionLevel > 60 && m_fearLevel < 50)
	{
		SetState(STATE_ATTACK);
	}
	else if (m_aggressionLevel < 40 && m_fearLevel > 50)
	{
		SetState(STATE_RUN);
	}
	//if (monster collide with trap)
	//{
	//	SetState(TRAPPED);
	//	if(timer > 5)
	//	SetState(Prev State);
	//}
	else
	{
		SetState(STATE_IDLE);
	}
}