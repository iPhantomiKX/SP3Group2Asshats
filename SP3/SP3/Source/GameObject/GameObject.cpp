#include "GameObject.h"

unsigned int createGO(World *world)
{
	for (unsigned GO = 0; GO < world->GAMEOBJECT_COUNT; ++GO)
	{
		if (world->mask[GO] == COMPONENT_NONE)
		{
			std::cout << "GO created" << std::endl;
			return(GO);
		}
	}
	std::cout << "Already at Max GOs" << std::endl;
    return(world->GAMEOBJECT_COUNT);
}

void destroyGO(World *world, unsigned int GO)
{
	std::cout << "GO destroyed" << std::endl;
	world->mask[GO] = COMPONENT_NONE;
}

#define MOVEMENT_MASK (COMPONENT_DISPLACEMENT | COMPONENT_VELOCITY)
void movementFunction(World *world, double dt)
{
    for (unsigned GO = 0; GO < world->GAMEOBJECT_COUNT; ++GO)
	{
		if ((world->mask[GO] & MOVEMENT_MASK) == MOVEMENT_MASK)
		{
			Vector3 *pos;
			Vector3 *vel;

			pos = &(world->position[GO]);
			vel = &(world->velocity[GO]);

			pos->x += vel->x * dt;
			pos->y += vel->y * dt;
			pos->z += vel->z * dt;
		}
	}
}

#define RENDER_MASK (COMPONENT_DISPLACEMENT | COMPONENT_APPEARANCE)
void renderFunction(World *world)
{
    for (unsigned GO = 0; GO < world->GAMEOBJECT_COUNT; ++GO)
	{
		if ((world->mask[GO] & RENDER_MASK) == RENDER_MASK)
		{
			Vector3 *pos;
			Mesh *mesh;

			pos = &(world->position[GO]);
			mesh = (world->mesh[GO]);

			std::cout << "rendering mesh at " << *pos << std::endl;
			//Call render
		}
	}
}