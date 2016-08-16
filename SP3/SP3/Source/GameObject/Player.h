/******************************************************************************/
/*!
\file	Player.h
\author Foo Jing Ting
\par	email: 152856H@mymail.nyp.edu.sg
\brief
Player class that stores the game's player variables
*/
/******************************************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include "Vector3.h"

/******************************************************************************/
/*!
Class Player:
\brief	A class that represents the player of the game
*/
/******************************************************************************/
class Player
{
public:
	enum MOVEMENT_STATE
	{
		MOVEMENT_STATE_WALK,
		//MOVEMENT_STATE_RUN,
		MOVEMENT_STATE_CROUCH,
		MOVEMENT_STATE_PRONE,
		MOVEMENT_STATE_TOTAL
	};

private:

public:
	Player();
	~Player();

	MOVEMENT_STATE m_movementState;
};

#endif