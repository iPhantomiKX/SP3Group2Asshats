#ifndef SCENE_GRASS_H
#define SCENE_GRASS_H

#include "../Scene.h"
#include "../../GameObject/ItemProjectiles.h"

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
	bool ViewCheckPosition(Vector3 pos, float degree);
    //Test stuff
	ItemProjectile* itemProjectile;

    //For placing traps
    bool placing = false;
	bool Capturing = false;
	bool Captured = false;
	int captureCounter = 0;

    std::vector<Vector3> placedTraps;

	//AABB HITBOX;

    World grass;

	AABB HITBOX;
    double counter;
    GameObject monster,rock,net;
};

#endif