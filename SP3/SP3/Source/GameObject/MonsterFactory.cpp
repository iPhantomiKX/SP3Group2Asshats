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

int MonsterFactory::monsterTypesQuantity = 0;

int MonsterFactory::GetMonsterTypesQuantity()
{
    return monsterTypesQuantity;
}
void MonsterFactory::SetMonsterTypesQuantity(int quantity)
{
    monsterTypesQuantity = quantity;
}

Monster* MonsterFactory::CreateMonster(std::string name)
{
    return 0;
}