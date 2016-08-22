/******************************************************************************/
/*!
\file	AI_Strategy.h
\author Muhammad Amirul Bin Zaol-kefli
\par	email: 150509T@mymail.nyp.edu.sg
\brief
Class that Updates the strategy of monster
*/
/******************************************************************************/
#ifndef AI_STRATEGY_H
#define AI_STRATEGY_H

#include "Vector3.h"
#include "Monster.h"
#include "Player.h"
#include "AABB.h"

class AI_Strategy
{
public:
	AI_Strategy();
	~AI_Strategy();

	enum STRATEGY_MODE
	{
		IDLE,
		ATTACK,
		RUN,
		TRAPPED,	//stun
		TOTAL_AI_STATE,
	};
	AI_Strategy::STRATEGY_MODE GetCurrentStrategy();
	void SetState(AI_Strategy::STRATEGY_MODE currentState);
	AI_Strategy::STRATEGY_MODE GetState();

	//virtual void SetDestination(Vector3 Destination);
	//virtual Vector3 GetPosition(Vector3 monsterPos);
	void Update();
	//virtual void SetDestination(Vector3 Destination) = 0;
	//virtual Vector3 GetPosition(Vector3 monsterPos) = 0;

	int CalculateDistance(Vector3 MonsterPos, Vector3 Destination);

	//Vector3 Destination;

private:
	STRATEGY_MODE currentState;
	AABB hitbox;
	//Vector3 destination;

	Player* player;
	Monster* monster;
	//std::vector<Vector3> placedTraps;
	//ItemProjectile* bait;
};

#endif