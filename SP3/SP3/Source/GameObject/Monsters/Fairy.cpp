#include "Fairy.h"

Boss_Fairy::Boss_Fairy(std::string name, int stats[]) : Monster(name, stats)
{
    m_strategy = NULL;
}

Boss_Fairy::~Boss_Fairy()
{
    if (m_strategy != NULL)
    {
        delete m_strategy;
        m_strategy = NULL;
    }
}

void Boss_Fairy::Update(double dt)
{
    // Do distance check between player, bait, traps

    // Do aggression change and fear change respectively
}