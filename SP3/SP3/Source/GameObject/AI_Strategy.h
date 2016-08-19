#ifndef AI_STRATEGY_H
#define AI_STRATEGY_H

#include "Vector3.h"

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
		TRAPPED
	};

	virtual void Update();
	virtual void SetDestination(const float x, const float y) = 0;

private:
	STRATEGY_MODE currentState;
};

#endif