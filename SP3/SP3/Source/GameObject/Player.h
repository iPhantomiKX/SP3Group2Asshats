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
#include "Items.h"
//#include <vector>

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
        MOVEMENT_STATE_IDLE,
        MOVEMENT_STATE_SLOW,
		MOVEMENT_STATE_WALK,
		MOVEMENT_STATE_RUN,
	};

    enum HEIGHT_STATE
    {
        HEIGHT_STATE_STANDING,
        HEIGHT_STATE_CROUCH,
        HEIGHT_STATE_PRONE,
        HEIGHT_STATE_JUMP,
        HEIGHT_STATE_TOTAL
    };

    Item inventory[Item::NUM_TYPE];

private:
    Vector3 position;
    Vector3 view;
    Vector3 up;
    Vector3 velocity;

    Vector3 prevVelocity;   // for decelerating movement when idle

    float eyeLevel;
    float speed;
    float jumpSpeed;
    float gravity;
    float jumpHeight;

    MOVEMENT_STATE m_movementState;
    HEIGHT_STATE m_heightState;

public:
	Player();
	~Player();

    Vector3 GetPositionVector();
    Vector3 GetViewVector();
    Vector3 GetUpVector();

    void Update(double dt);

    void Pitch(const double dt);
    void Yaw(const double dt);
    
    //void Walk();
    //void Run();
    void Crouch();
    //void Crawl();
    void Jump();

    void Move(const double dt);

    void UpdateStandUp(const double dt);
    void UpdateCrouch(const double dt);
    void UpdateJump(const double dt);
};

#endif