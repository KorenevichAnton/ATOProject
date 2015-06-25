#include "TankUnit.h"
#include "BattleModel.h"

using namespace cocos2d;
//----------------------------------------------------------------
TankUnit* TankUnit::create(BattleObject* _pBattleObject)
{
	TankUnit *pUnit = new TankUnit();
	if (pUnit && pUnit->init())
	{
		pUnit->pBattleObject = _pBattleObject;
		return pUnit;
	}
	delete pUnit;
	return NULL;
}

//----------------------------------------------------------------
TankUnit::TankUnit():
hp(5.0f),
moveSpeed(30.0f),
radius(120)//65
{

}

//----------------------------------------------------------------
TankUnit::~TankUnit()
{

}

//----------------------------------------------------------------
bool TankUnit::init()
{
	unitType = UT_TANK;
	return true;
}

//----------------------------------------------------------------
void TankUnit::release()
{
	delete this;
}

//----------------------------------------------------------------
void TankUnit::update(float _dt)
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
void TankUnit::moveUnit(float _dt)
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