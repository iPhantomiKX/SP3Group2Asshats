#include "Bird.h"

Monster_Bird::Monster_Bird(std::string name, int stats[]) : Monster(name, stats)
{
    m_strategy = NULL;
}

Monster_Bird::~Monster_Bird()
{
    if (m_strategy != NULL)
    {
        delete m_strategy;
        m_strategy = NULL;
    }
}

void Monster_Bird::Update(double dt)
{
    // Do distance check between player, bait, traps
    // Do aggression change and fear change respectively
    if ((GetPosition() - SharedData::GetInstance()->player->GetPositionVector()).LengthSquared() < 8)
    {
        changeAggressionStat(5);
        changeFearStat(-5);
    }
    else if ((GetPosition() - SharedData::GetInstance()->player->GetPositionVector()).LengthSquared() > 8)
    {
        GetAggressionStat();
        GetFearStat();
    }
    if (GetHealthStat() < 40)
    {
        changeAggressionStat(-5);
        changeFearStat(5);
    }
}