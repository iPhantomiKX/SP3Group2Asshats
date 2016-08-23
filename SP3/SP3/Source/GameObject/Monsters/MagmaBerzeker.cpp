#include "MagmaBerzeker.h"

Boss_MagmaBerzeker::Boss_MagmaBerzeker(std::string name, int stats[]) : Monster(name, stats)
{
    m_strategy = NULL;
}

Boss_MagmaBerzeker::~Boss_MagmaBerzeker()
{
    if (m_strategy != NULL)
    {
        delete m_strategy;
        m_strategy = NULL;
    }
}

void Boss_MagmaBerzeker::Update(double dt)
{

}