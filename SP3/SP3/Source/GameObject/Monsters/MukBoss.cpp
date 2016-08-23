#include "MukBoss.h"

Boss_MukBoss::Boss_MukBoss(std::string name, int stats[]) : Monster(name, stats)
{
    m_strategy = NULL;
}

Boss_MukBoss::~Boss_MukBoss()
{
    if (m_strategy != NULL)
    {
        delete m_strategy;
        m_strategy = NULL;
    }
}

void Boss_MukBoss::Update(double dt)
{

}