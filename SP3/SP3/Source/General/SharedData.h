#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include "../GameObject/Player.h"

class SharedData
{
	SharedData();
	~SharedData();

	Player* player;

public:
	static SharedData* GetInstance()
	{
		static SharedData sharedData;
		return &sharedData;
	}
};

#endif