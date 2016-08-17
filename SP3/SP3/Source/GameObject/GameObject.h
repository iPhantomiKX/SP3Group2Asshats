#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Vector3.h"
#include "../Graphics/Mesh/Mesh.h"
#include "AABB.h"
#include <iostream>

enum Components
{
	COMPONENT_NONE = 0,
	COMPONENT_DISPLACEMENT = 1 << 0,
	COMPONENT_VELOCITY = 1 << 1,
	COMPONENT_APPEARANCE = 1 << 2,
	COMPONENT_HITBOX = 1 << 3,
};

typedef int GameObject;	//Easier to reference

struct World
{
    static const int GAMEOBJECT_COUNT = 10;

	GameObject mask[GAMEOBJECT_COUNT];

	Vector3 position[GAMEOBJECT_COUNT];
	Vector3 velocity[GAMEOBJECT_COUNT];
	Mesh* mesh[GAMEOBJECT_COUNT];
	AABB hitbox[GAMEOBJECT_COUNT];
};

//"FetchGO"
unsigned int createGO(World *world);
void destroyGO(World *world, unsigned int GO);

//System managers
void movementFunction(World *world, double dt);
void renderFunction(World *world);
//ColliderManager;
//ProjectileManager;


#endif