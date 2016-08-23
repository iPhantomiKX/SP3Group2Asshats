#include "Rabbit.h"

Monster_Rabbit::Monster_Rabbit(std::string name, int stats[]) : Monster(name, stats)
{
    m_strategy = NULL;
}

Monster_Rabbit::~Monster_Rabbit()
{
    if (m_strategy != NULL)
    {
        delete m_strategy;
        m_strategy = NULL;
    }
}

void Monster_Rabbit::Update(double dt)
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