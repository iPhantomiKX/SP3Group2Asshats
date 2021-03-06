#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <Windows.h>
#include <iostream>

struct Key
{
public:
    unsigned short value;
    bool state;

    void Assign(unsigned short vk_key);
    bool isHeldDown;
    bool isPressed;
    bool isReleased;
    void Update();
};

class InputManager
{
public:
    enum KEY
    {
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,

        KEY_W,
        KEY_A,
        KEY_S,
        KEY_D,

        KEY_Q,
        KEY_E,

        KEY_G,
        KEY_X,

        KEY_SPACE,

        KEY_TAB,
        KEY_ENTER,
        KEY_CTRL,
        KEY_SHIFT,

        MOUSE_L,
        MOUSE_R,

        NUM_KEYS
    };

    Key keyState[NUM_KEYS];

    void Update();

    InputManager();
    ~InputManager();

private:
    
};




#endif