#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Vector3.h"
#include "../Graphics/Mesh/Mesh.h"
#include "AABB.h"
#include <iostream>

enum COMPONENTS
{
    COMPONENT_NONE = 0,
    COMPONENT_DISPLACEMENT = 1 << 0,
    COMPONENT_VELOCITY = 1 << 1,
    COMPONENT_APPEARANCE = 1 << 2,
    COMPONENT_HITBOX = 1 << 3,
    COMPONENT_TRAP = 1 << 4
    //COMPONENT_TOTAL
};

//Componenets
struct Appearance
{
    Vector3 scale;
    Mesh* mesh = nullptr;
};

struct AI_Script
{
    //Strategy start
    //Other stuff
};

struct Health
{
    int maxHealth;
    int currentHealth;
    int regenerationRate;
};

struct Trap_Script
{
    float radius;
    double effectTimer;
};

struct Projectile_Script
{
    float speed;
};

//GO is just an int with reference to the World componenets
typedef int GameObject;	

struct World
{
    static const int GAMEOBJECT_COUNT = 10;

	GameObject mask[GAMEOBJECT_COUNT];

	Vector3 position[GAMEOBJECT_COUNT];
	Vector3 velocity[GAMEOBJECT_COUNT];
    Appearance appearance[GAMEOBJECT_COUNT];
	AABB hitbox[GAMEOBJECT_COUNT];
    Trap_Script trap[GAMEOBJECT_COUNT];
};

//"FetchGO"
unsigned int createGO(World *world);
void destroyGO(World *world, unsigned int GO);

//System managers
//void movementFunction(World *world, double dt);
//void renderFunction(World *world);
//ColliderManager;
//ProjectileManager;



#endif