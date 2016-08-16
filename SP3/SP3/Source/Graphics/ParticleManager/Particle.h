/******************************************************************************/
/*!
\file	Particle.h
\author Muhammad Amirul Bin Zaol-kefli
\par	email: 150509T@mymail.nyp.edu.sg
\brief
Particle Manager
*/
/******************************************************************************/
#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3.h"

/******************************************************************************/
/*!
\brief
ParticleObject_TYPE enum
*/
/******************************************************************************/
enum ParticleObject_TYPE
{
	P_WATER = 0,
	P_BLOODSNOW,
	P_TOTAL
};

/******************************************************************************/
/*!
\brief
ParticleObject_TYPE class
*/
/******************************************************************************/
class ParticleObject
{
public:
	ParticleObject(ParticleObject_TYPE = P_WATER);
	~ParticleObject();

	ParticleObject_TYPE type;

	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	float rotation;
	float rotationSpeed;

	bool active;
};



#endif