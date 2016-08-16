#include "SharedData.h"

SharedData::SharedData()
{
}

void SharedData::Init()
{
	player = new Player();
	graphicsLoader = new GraphicsLoader();
	graphicsLoader->Init();
}

SharedData::~SharedData()
{
	if (player)
		delete player;

	if (graphicsLoader)
		delete graphicsLoader;
}