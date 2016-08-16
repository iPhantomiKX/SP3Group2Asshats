/****************************************************************************/
/*!
\file SceneManager.cpp
\author Bek Kunta
\par email: xiaobek\@gmail.com
\brief
A Class that handles the different scenes
*/
/****************************************************************************/
#include "SceneManager.h"
//#include "../Scene/MainMenu/MenuScene.h"
#include "../Scene/Zone 1/SceneSP3.h"

SceneManager::SceneManager() : m_scene(0)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::ChangeScene(short id)
{
	if (m_scene)
	{
		m_scene->Exit();
		delete m_scene;
	}

	if (id == 0)
	{
		//m_scene = new MenuScene();
	}
	else if (id == 1)
	{
		m_scene = new SceneSP3();
	}

	if (m_scene)
	{
		m_scene->Init();
	}
}

void SceneManager::Update(double dt)
{
	if (m_scene)
	{
		m_scene->Update(dt);
	}
}

void SceneManager::Render()
{
	if (m_scene)
	{
		m_scene->Render();
	}
}

void SceneManager::Exit()
{
	if (m_scene)
	{
		m_scene->Exit();
		delete m_scene;
	}
}