#ifndef __BattleObject__
#define __BattleObject__

#include "cocos2d.h"
#include "IBattleUnit.h"

class BattleModel;

class BattleObject
{
public:
	static BattleObject*	create();

	void					update(float _dt);
	void					release();

private:
	BattleObject();
	~BattleObject();

	bool					init();

public:
	void					setBattleUnit(IBattleUnit* _battleUnit) { battleUnit = _battleUnit; };
	IBattleUnit*			getBattleUnit() { return battleUnit; };

	void					setUnitGraphic(cocos2d::CCSprite* _unitGraphic) { unitGraphic = _unitGraphic; };
	cocos2d::CCSprite*		getUnitGraphic() { return unitGraphic; };

	void					setBattleModel(BattleModel* _pBattleModel) { pBattleModel = _pBattleModel; };
	BattleModel*			getBattleModel() { return pBattleModel; };	

private:
	IBattleUnit*			battleUnit;
	cocos2d::CCSprite*		unitGraphic;	
	
	BattleModel*			pBattleModel;

};

#endif //__BattleObject__