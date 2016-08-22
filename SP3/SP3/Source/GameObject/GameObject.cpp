#include "GameObject.h"

unsigned int createGO(World *world)
{
	for (unsigned GO = 0; GO < world->GAMEOBJECT_COUNT; ++GO)
	{
		if (world->mask[GO] == COMPONENT_NONE)
		{
			//Returns the first int that does not have a componenet/is inactive
            std::cout << "created go" << std::endl;
			return(GO);
		}
	}
	//Already at Max GOs
    std::cout << "at max go" << std::endl;
    return(world->GAMEOBJECT_COUNT);
}

void destroyGO(World *world, unsigned int GO)
{
    if ((world->mask[GO] & COMPONENT_DISPLACEMENT) == COMPONENT_DISPLACEMENT)
        world->position[GO].SetZero();

    if ((world->mask[GO] & COMPONENT_VELOCITY) == COMPONENT_VELOCITY)
        world->velocity[GO].SetZero();

    if ((world->mask[GO] & COMPONENT_APPEARANCE) == COMPONENT_APPEARANCE)
    {
        world->appearance[GO].scale.SetZero();
        world->appearance[GO].mesh = nullptr;
    }

    if ((world->mask[GO] & COMPONENT_HITBOX) == COMPONENT_HITBOX)
    {
        world->hitbox[GO].m_origin.SetZero();
        world->hitbox[GO].m_scale.SetZero();
    }

	world->mask[GO] = COMPONENT_NONE;
    std::cout << "destroyed go" << std::endl;
}