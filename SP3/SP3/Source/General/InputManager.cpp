#include "InputManager.h"

InputManager::InputManager()
{
    for (unsigned i = 0; i < NUM_KEYS; ++i)
    {
        keyState[i].state = false;
        keyState[i].isReleased = false;
        keyState[i].isHeldDown = false;
    }

    keyState[KEY_SPACE].Assign(VK_SPACE);

}


InputManager::~InputManager()
{
}


void InputManager::Update()
{
    for (unsigned i = 0; i < NUM_KEYS; ++i)
    {
        keyState[i].Update();
    }
}


void Key::Assign(unsigned short vk_key)
{
    this->value = vk_key;
}


//bool Key::IsHeldDown()
//{
//
//
//    return false;
//}
//
//bool Key::IsReleased()
//{
//
//
//    return false;
//}

bool Key::IsPressed()
{
    if ((GetAsyncKeyState(value) & 0x8000) != 0)
    {
        state = true;
        return true;
    }
    return false;
}

void Key::Update()
{
    state = false;
    isReleased = false;

    if (isHeldDown && (GetAsyncKeyState(value) & 0x8000) != 0)
        isHeldDown = true;
    else if (isHeldDown && !(GetAsyncKeyState(value) & 0x8000) != 0)
    {   
        isHeldDown = false;
        isReleased = true;
    }

    if (!state && (GetAsyncKeyState(value) & 0x8000) != 0)
    {
        isHeldDown = true;
        state = true;
    }
    else if (state && !(GetAsyncKeyState(value) & 0x8000) != 0)
    {
        state = false;
    }


}