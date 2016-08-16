/******************************************************************************/
/*!
\file	SharedData.cpp
\author Foo Jing Ting
\par	email: 152856H\@mymail.nyp.edu.sg
\brief
Singleton class that contains variables and objects needed by different files
*/
/******************************************************************************/
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