/******************************************************************************/
/*!
\file	Player.cpp
\author Foo Jing Ting
\par	email: 152856H\@mymail.nyp.edu.sg
\brief
Player class that stores the game's player variables
*/
/******************************************************************************/
#include "Player.h"
#include "MyMath.h"
#include "../General/Application.h"

Player::Player()
{
    position.SetZero();
    velocity.SetZero();
    view.Set(1, 0, 0);
    up.Set(0, 1, 0);

    eyeLevel = 5.f;
    speed = 0.f;
    jumpSpeed = 0.f;
    gravity = -100.f;
    jumpHeight = 0.f;

    m_movementState = MOVEMENT_STATE_IDLE;
    m_heightState = HEIGHT_STATE_STANDING;

    Item tempInventory[Item::NUM_TYPE] =
    {
        Item("", Item::TYPE_NET, 10, 100, 10),
        Item("", Item::TYPE_NET, 10, 100, 10)
    };

    for (unsigned i = 0; i < Item::NUM_TYPE; ++i)
    {
        inventory[i] = tempInventory[i];
    }

}

Player::~Player()
{
}

Vector3 Player::GetPositionVector()
{
    return position;
}

Vector3 Player::GetViewVector()
{
    return view;
}

Vector3 Player::GetUpVector()
{
    return up;
}

static const float CAMERA_SPEED = 5.0f;

void Player::Update(double dt)
{
    m_movementState = MOVEMENT_STATE_IDLE;
    velocity.SetZero();

    if (Application::IsKeyPressed('W'))
    {
        m_movementState = MOVEMENT_STATE_WALK;
        //MoveForward(dt);

        velocity += view.Normalized();
    }
    if (Application::IsKeyPressed('S'))
    {
        m_movementState = MOVEMENT_STATE_WALK;
        //MoveBackward(dt);
        velocity += -view.Normalized();
    }
    if (Application::IsKeyPressed('A'))
    {
        m_movementState = MOVEMENT_STATE_WALK;
        //MoveLeft(dt);
        // set velocity here
        Vector3 right = view.Cross(up);
        right.y = 0;
        right.Normalize();
        velocity += -right;
    }
    if (Application::IsKeyPressed('D'))
    {
        m_movementState = MOVEMENT_STATE_WALK;
        //MoveRight(dt);
        Vector3 right = view.Cross(up);
        right.y = 0;
        right.Normalize();
        velocity += right;
    }

    if (velocity.LengthSquared() > Math::EPSILON)
    {
        velocity.Normalized();
        prevVelocity = velocity;
    }

    if (Application::IsKeyPressed(VK_CONTROL))
    {
        Crouch();
    }
    if (Application::IsKeyPressed(VK_SPACE))
    {
        Jump();
    }

    if (Application::IsKeyPressed(VK_SHIFT))
    {
        if (m_heightState == HEIGHT_STATE_STANDING)
        {
            m_movementState = MOVEMENT_STATE_RUN;
        }
    }

    if (m_heightState == HEIGHT_STATE_CROUCH)
    {
        m_movementState = MOVEMENT_STATE_SLOW;
    }

    switch (m_movementState)
    {
    case MOVEMENT_STATE_IDLE:
        //speed = 0;
        if (speed != 0.f)
        {
            speed -= 40.f * (float)(dt);
            if (speed < 0.f)
                speed = 0.f;
        }
        velocity = prevVelocity;
        break;

    case MOVEMENT_STATE_SLOW:
        //speed = 5.f;
        if (speed > 5.f)
        {
            speed -= 40.f * (float)(dt);
            if (speed < 5.f)
                speed = 5.f;
        }
        else if (speed < 5.f)
        {
            speed += 40.f * (float)(dt);
            if (speed > 5.f)
                speed = 5.f;
        }
        break;

    case MOVEMENT_STATE_WALK:
        //speed = 20.f;
        if (speed > 20.f)
        {
            speed -= 40.f * (float)(dt);
            if (speed < 20.f)
                speed = 20.f;
        }
        else if (speed < 20.f)
        {
            speed += 40.f * (float)(dt);
            if (speed > 20.f)
                speed = 20.f;
        }
        break;

    case MOVEMENT_STATE_RUN:
        //speed = 60.f;
        if (speed > 60.f)
        {
            speed -= 50.f * (float)(dt);
            if (speed < 60.f)
                speed = 60.f;
        }
        else if (speed < 60.f)
        {
            speed += 50.f * (float)(dt);
            if (speed > 60.f)
                speed = 60.f;
        }
        break;
    }


    Move(dt);

    //Move(dt); // move by Vector3 velocity

    // Turn player's view
    double x, y;
    Application::GetCursorPos(&x, &y);

    if (x != Application::cursorXPos)
    {
        double diff_xpos = Application::cursorXPos - x;

        //Vector3 view = (target - position).Normalized();
        float yaw = (float)(diff_xpos * CAMERA_SPEED * (float)dt);
        Mtx44 rotation;
        rotation.SetToRotation(yaw, 0, 1, 0);
        view = rotation * view;
        //target = position + view;
        Vector3 right = view.Cross(up);
        right.y = 0;
        right.Normalize();
        up = right.Cross(view).Normalized();
    }
    if (y != Application::cursorYPos - 0.5)
    {
        double diff_ypos = Application::cursorYPos - y;

        float pitch = (float)(diff_ypos * CAMERA_SPEED * (float)dt);
        //Vector3 view = (target - position).Normalized();
        Vector3 right = view.Cross(up);
        right.y = 0;
        right.Normalize();
        up = right.Cross(view).Normalized();
        Mtx44 rotation;
        rotation.SetToRotation(pitch, right.x, right.y, right.z);
        view = rotation * view;
        //target = position + view;
    }
}

void Player::Pitch(const double dt)
{

}

void Player::Yaw(const double dt)
{

}

void Player::Move(const double dt)
{
    position += velocity * speed * (float)dt;

    std::cout << speed << std::endl;
    
    switch (m_heightState)
    {
    case HEIGHT_STATE_STANDING:
        UpdateStandUp(dt);
        break;

    case HEIGHT_STATE_CROUCH:
        UpdateCrouch(dt);
        break;

    case HEIGHT_STATE_JUMP:
        UpdateJump(dt);
        break;

    case HEIGHT_STATE_PRONE:
        break;
    }

    position.y = eyeLevel + jumpHeight;
}

void Player::Crouch()
{
    if (m_heightState != HEIGHT_STATE_CROUCH && eyeLevel == 5.f) {
        m_heightState = HEIGHT_STATE_CROUCH;
    }

    if (m_heightState == HEIGHT_STATE_CROUCH && eyeLevel == 1.f) {
        m_heightState = HEIGHT_STATE_STANDING;
    }
}

void Player::Jump()
{
    if (m_heightState != HEIGHT_STATE_JUMP && m_heightState != HEIGHT_STATE_PRONE) {
        m_heightState = HEIGHT_STATE_JUMP;

        jumpSpeed = 30.f;    //dt not needed
    }
}

void Player::UpdateStandUp(const double dt)
{
    if (eyeLevel < 25.f) {
        eyeLevel += (float)(20.f * dt);
        eyeLevel = Math::Min(5.f, eyeLevel);
    }
}

void Player::UpdateCrouch(const double dt)
{
    eyeLevel -= (float)(20.f * dt);
    eyeLevel = Math::Max(1.f, eyeLevel);
}

void Player::UpdateJump(const double dt)
{
    // Factor in gravity
    jumpSpeed += (float)(gravity * dt);

    // Update camera and target position

    jumpHeight += jumpSpeed * (float)dt;

    // Check if camera reached the ground
    float newHeight = position.y + jumpHeight;  //player would be in the ground already
    if (newHeight + 1.f <= position.y)
    {
        // Camera landing on ground
        position.y = newHeight;

        //when landing, reduce MoveVel (impact)
        speed = Math::Max(0.f, speed - 20.f);

        // Reset values
        jumpSpeed = 0.f;
        m_heightState = HEIGHT_STATE_STANDING;
        jumpHeight = 0.f;
    }
}