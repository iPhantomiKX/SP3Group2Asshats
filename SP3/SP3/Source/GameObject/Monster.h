/******************************************************************************/
/*!
\file	Monster.h
\author Foo Jing Ting
\par	email: 152856H@mymail.nyp.edu.sg
\brief
Class that defines a monster's variables and statistics
*/
/******************************************************************************/
#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "Vector3.h"

class Monster
{
public:
    virtual ~Monster();
    
    std::string GetName();
    int GetHealthStat();
    int GetCaptureRateStat();
    int GetAggressionStat();
    int GetFearStat();
    bool CheckCapture();

	virtual void Update(double dt);

protected:
	Monster();

    std::string m_name;

    int m_healthStat;
    int m_captureRateStat; 
    int m_aggressionStat;
    int m_fearStat;

    // Mesh_type OR
    // Enemy_type

    // Strategy* strategy;

    Vector3 m_position;
    Vector3 m_velocity;
    Vector3 m_scale;  // for rendering

    void move();
    void changeHealthStat(const int damage);
    void changeAggressionStat(const int aggression);
    void changeFearStat(const int fear);
    void changeCaptureRateStat(const int captureRate);
};

#endif