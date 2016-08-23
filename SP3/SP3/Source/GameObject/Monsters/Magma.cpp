#include "Magma.h"

Monster_Magma::Monster_Magma(std::string name, int stats[]) : Monster(name, stats)
{
    m_strategy = NULL;
}

Monster_Magma::~Monster_Magma()
{
    if (m_strategy != NULL)
    {
        delete m_strategy;
        m_strategy = NULL;
    }
}

void Monster_Magma::Update(double dt)
{

}