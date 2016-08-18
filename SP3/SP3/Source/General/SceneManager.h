/****************************************************************************/
/*!
\file SceneManager.h
\author Bek Kunta
\par email: xiaobek\@gmail.com
\brief
A Class that handles the different scenes
*/
/****************************************************************************/
#include "../Scene/Scene.h"

/****************************************************************************/
/*!
Class SceneManager:
\brief Defines a class that manages the different scenes in gameplay
*/
/****************************************************************************/
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	Scene* m_scene;

	void ChangeScene(short id);

	void Update(double dt);
	void Render();
	void Exit();
};