#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "Vector3.h"

class Monster
{
public:
    Monster();
    ~Monster();
    
    std::string GetName();
    int GetHealthStat();
    int GetCaptureRateStat();
    int GetAggressionStat();
    int GetFearStat();
    bool CheckCapture();

protected:
    std::string m_name;

    int m_healthStat;
    int m_captureRateStat; 
    int m_aggressionStat;
    int m_fearStat;

    // Mesh_type OR
    // Enemy_type

    // Strategy* strategy;

    Vector3 position;
    Vector3 velocity;
    Vector3 scale;  // for rendering

    void move();
    void changeHealthStat(int damage);
    void changeAggressionStat(int aggression);
    void changeFearStat(int fear);
    void changeCaptureRateStat(int captureRate);
}

#endif