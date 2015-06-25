#include "BattleObject.h"
#include "time.h"
#include "stdlib.h"

//----------------------------------------------------------------
BattleObject* BattleObject::create()
{
	BattleObject *pUnit = new BattleObject();
	if(pUnit && pUnit->init())
	{
		return pUnit;
	}
	delete pUnit;
	return NULL;
}

//----------------------------------------------------------------
BattleObject::BattleObject():
	battleUnit(NULL),
	unitGraphic(NULL),
	pBattleModel(NULL)
{
	
}

//----------------------------------------------------------------
BattleObject::~BattleObject()
{

}

//----------------------------------------------------------------
bool BattleObject::init()
{
	return true;
}

//----------------------------------------------------------------
void BattleObject::release()
{
	this->getBattleUnit()->release();
	this->unitGraphic->removeFromParentAndCleanup(true);
	this->unitGraphic = NULL;
	delete this;
}

//----------------------------------------------------------------
void BattleObject::update(float _dt)
{
	this->unitGraphic->setPosition(this->battleUnit->getPosition());
	this->battleUnit->update(_dt);
}

//----------------------------------------------------------------
//----------------------------------------------------------------