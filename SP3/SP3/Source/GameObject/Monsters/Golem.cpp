#include "Golem.h"

Monster_Golem::Monster_Golem(std::string name, int stats[]) : Monster(name, stats)
{
    m_strategy = NULL;
}

Monster_Golem::~Monster_Golem()
{
    if (m_strategy != NULL)
    {
        delete m_strategy;
        m_strategy = NULL;
    }
}

void Monster_Golem::Update(double dt)
{

}