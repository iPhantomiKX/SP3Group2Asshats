/******************************************************************************/
/*!
\file	MonsterFactory.cpp
\author Foo Jing Ting
\par	email: 152856H@mymail.nyp.edu.sg
\brief
Class that creates Monsters inside a scene
*/
/******************************************************************************/
#include "MonsterFactory.h"

MonsterFactory::monsterStatsMap MonsterFactory::m_monsterStatsList = {};

MonsterFactory::MonsterFactory()
{
}

MonsterFactory::~MonsterFactory()
{
}

Monster* MonsterFactory::CreateMonster(std::string name)
{
    return 0;
}

void MonsterFactory::AddToMap(std::string name, int stats[])
{
    size_t size = sizeof(stats) / sizeof(int);

    std::cout << size;

    int tempArray[5];
    for (int i = 0; i < 5; ++i)
    {
        tempArray[i] = stats[i];
    }
    m_monsterStatsList.insert(std::pair<std::string, int(*)[5]>(name, &tempArray));
}