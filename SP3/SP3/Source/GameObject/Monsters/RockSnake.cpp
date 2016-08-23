#include "RockSnake.h"

Boss_RockSnake::Boss_RockSnake(std::string name, int stats[]) : Monster(name, stats)
{
    m_strategy = NULL;
}

Boss_RockSnake::~Boss_RockSnake()
{
    if (m_strategy != NULL)
    {
        delete m_strategy;
        m_strategy = NULL;
    }
}

void Boss_RockSnake::Update(double dt)
{

}