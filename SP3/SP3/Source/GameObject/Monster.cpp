/******************************************************************************/
/*!
\file	Monster.cpp
\author Foo Jing Ting
\par	email: 152856H@mymail.nyp.edu.sg
\brief
Class that defines a monster's variables and statistics
*/
/******************************************************************************/
#include "Monster.h"

Monster::Monster()
{
    // idea: Monster(std::string name);
    // based on name, retrieve stats from a struct/array that already initialised with the stats from the text files
}

Monster::~Monster()
{
}

std::string Monster::GetName()
{
    return m_name;
}

int Monster::GetHealthStat()
{
    return m_healthStat;
}

int Monster::GetCaptureRateStat()
{
    return m_captureRateStat;
}

int Monster::GetAggressionStat()
{
    return m_aggressionStat;
}

int Monster::GetFearStat()
{
    return m_fearStat;
}

bool Monster::CheckCapture()
{
    return false;
}


void Monster::move()
{
    m_position += m_velocity;   // * dt
}

void Monster::changeHealthStat(int damage)
{
    m_healthStat += damage;
}

void Monster::changeAggressionStat(int aggression)
{
    m_aggressionStat += aggression;
}

void Monster::changeFearStat(int fear)
{
    m_fearStat += fear;
}

void Monster::changeCaptureRateStat(int captureRate)
{
    m_captureRateStat += captureRate;
}