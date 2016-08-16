#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include "../GameObject/Player.h"
#include "../Graphics/GraphicsLoader/GraphicsLoader.h"

class SharedData
{
	SharedData();
	~SharedData();

public:
	void Init();

	static SharedData* GetInstance()
	{
		static SharedData sharedData;
		return &sharedData;
	}

	Player* player;
	GraphicsLoader* graphicsLoader;
};

#endif