#include "BattleUnitFactory.h"
#include "SimpleSoldierUnit.h"
#include "TankUnit.h"

//---------------------------------------------------------------
BattleObject* BattleUnitFactory::createUnit(unit _unit, BattleModel* _pBattleModel)
{
	BattleObject* pBattleObject = BattleObject::create();
	IBattleUnit* pBattleUnit;
	cocos2d::CCSprite* graphic;

	if(_unit.m_type == UT_SIMPLE_SOLDIER)
	{
		pBattleUnit = SimpleSoldierUnit::create(pBattleObject);
		//
		graphic = cocos2d::CCSprite::create("textures/scenes/battle/gamePeople.png");
		
	}
	if(_unit.m_type == UT_TANK)
	{
		pBattleUnit = TankUnit::create(pBattleObject);
		//
		graphic = cocos2d::CCSprite::create("textures/scenes/battle/tank.png");
	}

	pBattleObject->setBattleUnit(pBattleUnit);
	//
	graphic->setAnchorPoint(ccp(0.5, 0.5));
	pBattleObject->setUnitGraphic(graphic);

	pBattleObject->setBattleModel(_pBattleModel);
	return pBattleObject;
}