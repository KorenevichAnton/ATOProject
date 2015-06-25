#include "SimpleSoldierUnit.h"
#include "BattleModel.h"

using namespace cocos2d;
//----------------------------------------------------------------
SimpleSoldierUnit* SimpleSoldierUnit::create(BattleObject* _pBattleObject)
{
	SimpleSoldierUnit *pUnit = new SimpleSoldierUnit();
	if (pUnit && pUnit->init())
	{
		pUnit->pBattleObject = _pBattleObject;
		return pUnit;
	}
	delete pUnit;
	return NULL;
}

//----------------------------------------------------------------
SimpleSoldierUnit::SimpleSoldierUnit():
hp(3.0f),
moveSpeed(30.0f),//2.2
radius(45)
{

}

//----------------------------------------------------------------
SimpleSoldierUnit::~SimpleSoldierUnit()
{

}

//----------------------------------------------------------------
bool SimpleSoldierUnit::init()
{
	unitType = UT_SIMPLE_SOLDIER;
	return true;
}

//----------------------------------------------------------------
void SimpleSoldierUnit::release()
{
	delete this;
}

//----------------------------------------------------------------
void SimpleSoldierUnit::update(float _dt)
{
	//is unit destroyed
	if(this->hp <= 0)
	{
		this->getBattleObject()->getBattleModel()->removeUnit(this->getBattleObject());
		return;
	}
	//move unit
	this->moveUnit(_dt);
}

//----------------------------------------------------------------
void SimpleSoldierUnit::moveUnit(float _dt)
{
	this->position.y -= this->moveSpeed * _dt;
	if(this->position.y < 0)
	{
		this->getBattleObject()->getBattleModel()->removeUnit(this->getBattleObject());
		Memory->setHp(Memory->getHp() - 1);
	}
}

//----------------------------------------------------------------
//----------------------------------------------------------------