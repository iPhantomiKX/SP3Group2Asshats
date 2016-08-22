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
#include <map>
#include "Monster.h"

class MonsterFactory
{
    //static int monsterTypesQuantity;
    typedef std::map<std::string, int(*)[5]> monsterStatsMap;
    static monsterStatsMap m_monsterStatsList;

public:
    static void LoadMonsterData(const char* file_path);

    //static int GetMonsterTypesQuantity();
    //static void SetMonsterTypesQuantity(int quantity);

    static Monster* CreateMonster(std::string name); // change to const

    static void AddToMap(std::string, int stats[5]);

        // generate components for the gameobject instead
        // AI is a component -- if yes, AIcomponent->Update()
};

#endif