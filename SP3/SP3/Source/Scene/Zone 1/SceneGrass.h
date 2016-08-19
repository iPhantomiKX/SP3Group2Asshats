#ifndef SCENE_GRASS_H
#define SCENE_GRASS_H

#include "../Scene.h"
#include "../../GameObject/ItemProjectiles.h"
#include "../../GameObject/AABB.h"

class SceneGrass : public Scene
{
	float m_worldHeight;
	float m_worldWidth;

	// Clicking
	bool bLButtonState;

public:
	SceneGrass();
	~SceneGrass();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void RenderGrassScene();
	virtual void Exit();

	ItemProjectile* itemProjectile;

	AABB hitbox;
};

#endif