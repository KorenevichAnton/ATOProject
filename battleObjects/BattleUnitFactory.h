#ifndef __BattleUnitFactory__
#define __BattleUnitFactory__

#include "BattleObject.h"
#include "BattleModel.h"

class BattleUnitFactory
{
public:
	static BattleObject* createUnit(unit _unit, BattleModel* _pBattleModel);
};

#endif //__BattleUnitFactory__