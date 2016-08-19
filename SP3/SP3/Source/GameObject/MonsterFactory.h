/******************************************************************************/
/*!
\file	MonsterFactory.h
\author Foo Jing Ting
\par	email: 152856H@mymail.nyp.edu.sg
\brief
Class that creates Monsters inside a scene
*/
/******************************************************************************/
#ifndef MONSTER_FACTORY_H
#define MONSTER_FACTORY_H

#include <string>
#include "Monster.h"

class MonsterFactory
{
    static int monsterTypesQuantity;

public:
    //static array of stats;
    static int** statArray[6];

    MonsterFactory();
    ~MonsterFactory();

    static int GetMonsterTypesQuantity();
    static void SetMonsterTypesQuantity(int quantity);

    static Monster* CreateMonster(std::string name);
        // generate components for the gameobject instead
        // AI is a component -- if yes, AIcomponent->Update()
};

#endif