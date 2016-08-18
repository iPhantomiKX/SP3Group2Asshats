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

Player::Player()
{
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