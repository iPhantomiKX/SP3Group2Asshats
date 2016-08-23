#ifndef MONSTER_BOSS_MUKBOSS_H
#define MONSTER_BOSS_MUKBOSS_H

#include "../Monster.h"
#include "../../General/SharedData.h"

class Boss_MukBoss : public Monster
{
public:
    Boss_MukBoss(std::string name, int stats[]);
    virtual ~Boss_MukBoss();

	//Monster Movement update
    virtual void Update(double dt);
};

#endif