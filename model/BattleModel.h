#ifndef __BattleModel__
#define __BattleModel__

#include "BattleObject.h"

class BattleModel
{
public:
	static BattleModel*				create();

private:
	BattleModel();
	~BattleModel();

	bool							init();

public:
	void							update(float _dt);

	void							release();
	//
	void							generateUnit(float _dt, cocos2d::CCLayer* _pBattleLayer);
	//
	void							addUnit(BattleObject* _unit);
	void							removeUnit(BattleObject* _unit);

	void							shot(cocos2d::CCPoint _position);
	//
	std::vector<BattleObject*>&		getBattleUnits() { return battleUnits; };

	bool							canGenerate(cocos2d::CCPoint _point, float _radius);

private:
	std::vector<BattleObject*>		battleUnits;
	
	//Generation units
	BattleObject*				genBattleObject();
	BattleObject*				getGeneratedObject(BattleUnitType _object);

	float						genDelay;						
	float						genTime;
	cocos2d::CCPoint			genPosition;

	//
	BattleUnitType				genUnitType;
	//

	int							genZ;
};

#endif //__BattleModel__