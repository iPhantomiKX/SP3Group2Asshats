#ifndef MONSTER_FACTORY_H
#define MONSTER_FACTORY_H

#include <string>
#include "Monster.h"

class MonsterFactory
{
    //static array of stats;

public:
    MonsterFactory();
    ~MonsterFactory();

    static Monster* CreateMonster(std::string name);
        // generate components for the gameobject instead
        // AI is a component -- if yes, AIcomponent->Update()
};

#endif