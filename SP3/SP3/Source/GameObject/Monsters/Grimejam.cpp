#include "Grimejam.h"

Monster_Grimejam::Monster_Grimejam(std::string name, int stats[]) : Monster(name, stats)
{
    m_strategy = NULL;
}

Monster_Grimejam::~Monster_Grimejam()
{
    if (m_strategy != NULL)
    {
        delete m_strategy;
        m_strategy = NULL;
    }
}

void Monster_Grimejam::Update(double dt)
{

}