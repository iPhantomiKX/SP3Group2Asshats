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

/*void Monster_Bird::Update(double dt)
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
}*/

void Monster_Bird::Update(double dt)
{
    // Do distance check between player, bait, traps
    // Do aggression change and fear change respectively
    // Distance adjust later for stabilising
    //Default state condition
    if ((GetPosition() - SharedData::GetInstance()->player->GetPositionVector()).LengthSquared() > 16)
    {
        changeAggressionStat(20);
        changeFearStat(0);
    }
    if ((GetPosition() - SharedData::GetInstance()->player->GetPositionVector()).LengthSquared() < 16)
    {
        AggressionLevel += (10 * dt);
        changeAggressionStat(AggressionLevel);
        if (AggressionLevel >= 100)
        {
            AggressionLevel = 100;
        }
    }
    if (GetHealthStat() < 40)
    {
        AggressionLevel -= 20 * dt;
        FearLevel = 60 + (2 * dt);
        changeAggressionStat(AggressionLevel);
        changeFearStat(FearLevel);
        if (AggressionLevel <= 0)
        {
            AggressionLevel = 0;
        }
        if (FearLevel >= 100)
        {
            FearLevel = 100;
        }
    }
    // if distance > 16, decrease Aggression and Fear to original
    GetAggressionStat();
    GetFearStat();
}
