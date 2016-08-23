#include "Kof.h"

Monster_Kof::Monster_Kof(std::string name, int stats[]) : Monster(name, stats)
{
    m_strategy = NULL;
}

Monster_Kof::~Monster_Kof()
{
    if (m_strategy != NULL)
    {
        delete m_strategy;
        m_strategy = NULL;
    }
}

void Monster_Kof::Update(double dt)
{

}