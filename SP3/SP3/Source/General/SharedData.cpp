#include "SharedData.h"

SharedData::SharedData()
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