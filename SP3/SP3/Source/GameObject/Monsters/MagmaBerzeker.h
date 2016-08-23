#ifndef MONSTER_BOSS_MAGMA_BERZEKER_H
#define MONSTER_BOSS_MAGMA_BERZEKER_H

#include "../Monster.h"
#include "../../General/SharedData.h"

class Boss_MagmaBerzeker : public Monster
{
public:
    Boss_MagmaBerzeker(std::string name, int stats[]);
    virtual ~Boss_MagmaBerzeker();

	//Monster Movement update
    virtual void Update(double dt);
};

#endif