#include "SharedData.h"

SharedData::SharedData()
{
}

void SharedData::Init()
{
	player = new Player();
	graphicsLoader = new GraphicsLoader();
    inputManager = new InputManager();
	graphicsLoader->Init();
}

SharedData::~SharedData()
{
	if (player)
		delete player;

	if (graphicsLoader)
		delete graphicsLoader;

    if (inputManager)
        delete inputManager;
}