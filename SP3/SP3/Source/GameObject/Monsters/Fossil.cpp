#include "Fossil.h"

Monster_Fossil::Monster_Fossil(std::string name, int stats[]) : Monster(name, stats)
{
    m_strategy = NULL;
}

Monster_Fossil::~Monster_Fossil()
{
    if (m_strategy != NULL)
    {
        delete m_strategy;
        m_strategy = NULL;
    }
}

void Monster_Fossil::Update(double dt)
{

}