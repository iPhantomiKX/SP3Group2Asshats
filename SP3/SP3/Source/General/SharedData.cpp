#include "SharedData.h"

SharedData::SharedData()
{
	player = new Player();
}

SharedData::~SharedData()
{
	if (player)
	{
		delete player;
	}
}