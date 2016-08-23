#include "FireBugs.h"

Monster_FireBugs::Monster_FireBugs(std::string name, int stats[]) : Monster(name, stats)
{
    m_strategy = NULL;
}

Monster_FireBugs::~Monster_FireBugs()
{
    if (m_strategy != NULL)
    {
        delete m_strategy;
        m_strategy = NULL;
    }
}

void Monster_FireBugs::Update(double dt)
{

}