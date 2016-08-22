#ifndef RABBIT_H
#define RABBIT_H

#include "../Monster.h"

class Monster_Rabbit : public Monster
{
public:
    Monster_Rabbit(std::string name, int stats[]) : Monster(name, stats)
    {
        Strategy = NULL;
    }
    virtual ~Monster_Rabbit()
    {
        if (Strategy != NULL)
        {
            delete Strategy;
            Strategy = NULL;
        }
    }

    void ChangeStrategy(AI_Strategy* newAI, bool bDelete)
    {
        if (bDelete == true)
        {
            if (Strategy != NULL)
            {
                delete Strategy;
                Strategy = NULL;
            }
        }
        Strategy = newAI;
    }

    //Monster Movement update
    virtual void Update(double dt)
    {

    }
};

#endif