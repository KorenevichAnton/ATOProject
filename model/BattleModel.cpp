#include "BattleModel.h"
#include "BattleUnitFactory.h"
#include "DataLoader.h"

#include "BattleScene.h"

#include <vector>

#define COCOS2D_DEBUG 1

using namespace cocos2d;
using namespace std;

//---------------------------------------------------------------
BattleModel* BattleModel::create()
{
	BattleModel *pModel = new BattleModel();
	if(pModel && pModel->init())
	{
		return pModel;
	}
	delete pModel;
	return NULL;
}

//---------------------------------------------------------------
BattleModel::BattleModel():
genDelay(0.1f),
genTime(0.0f),//0
genPosition(cocos2d::CCPointZero),
genZ(10000),
genUnitType(UT_NONE)
{
	battleUnits.clear();
}

//---------------------------------------------------------------
BattleModel::~BattleModel()
{
	battleUnits.clear();
}

//---------------------------------------------------------------
bool BattleModel::init()
{
	srand(time(NULL));
	return true;
}

//---------------------------------------------------------------
void BattleModel::update(float _dt)
{
	this->generateUnit(_dt, BattleScene::pSelf);
	
	//battleUnits[0]->update(_dt);
	for(vector<BattleObject*>::iterator it = battleUnits.begin() ; it < battleUnits.end() ; it++)
	{
		if((*it))	
			(*it)->update(_dt);
	}
}

//---------------------------------------------------------------
void BattleModel::release()
{
	delete this;
}

//---------------------------------------------------------------
void BattleModel::addUnit(BattleObject* _unit)
{
	this->battleUnits.push_back(_unit);
}

//---------------------------------------------------------------
void BattleModel::removeUnit(BattleObject* _unit)
{
	for(vector<BattleObject*>::iterator it = battleUnits.begin() ; it < battleUnits.end() ; it++)
	{
		if((*it) == _unit)
		{
			_unit->release();
			this->battleUnits.erase(it);
			break;
		}
	}
}

//---------------------------------------------------------------
BattleObject* BattleModel::genBattleObject()
{
	std::vector<unit> units = Loader->getCurCity()->m_units;
	int randEdge = units[units.size() - 1].m_genPercent - 1;
	for(vector<unit>::iterator it = units.begin() ; it < units.end() ; it++)
	{
		if((*it).m_genPercent > rand() % randEdge)
		{
			this->genUnitType = (*it).m_type;
			return BattleUnitFactory::createUnit((*it), this);
		}
	}	
	/*
	if(rand()%100 <= 25)
	{
		this->genUnitType = UT_SIMPLE_SOLDIER;
		return BattleUnitFactory::createUnit("simpleSoldier", this);
	}
	else 
	{
		this->genUnitType = UT_TANK;
		return BattleUnitFactory::createUnit("tank", this);
	}
	*/
}

//---------------------------------------------------------------
BattleObject* BattleModel::getGeneratedObject(BattleUnitType _object)
{
	std::vector<unit> units = Loader->getCurCity()->m_units;
	for(vector<unit>::iterator it = units.begin() ; it < units.end() ; it++)
	{
		if(_object == (*it).m_type)
			return BattleUnitFactory::createUnit((*it), this);
	}
	//else if(_object == UT_TANK)
	//	return BattleUnitFactory::createUnit("tank", this);
}

//---------------------------------------------------------------
bool BattleModel::canGenerate(CCPoint _point, float _radius)
{
	if(this->battleUnits.size() == 0)
		return true;
	for(vector<BattleObject*>::iterator it = battleUnits.begin() ; it < battleUnits.end() ; it++)
	{
		float distance = ccpDistance((*it)->getBattleUnit()->getPosition(), _point);
		if(fabs(distance) < _radius + (*it)->getBattleUnit()->getRadius())
		{
			return false;
		}
	}
	return true;
}

//---------------------------------------------------------------
void BattleModel::generateUnit(float _dt, cocos2d::CCLayer* pBattleLayer)
{
	CCPoint randomPoint = ccp(48 + rand() % 720, 1050);

	if(this->genTime > this->genDelay)
	{
		BattleObject* unit = NULL;

		if(this->genUnitType == UT_NONE)
			unit = this->genBattleObject();
		else
			unit = this->getGeneratedObject(this->genUnitType);

		if(this->canGenerate(randomPoint, unit->getBattleUnit()->getRadius()))
		{
			this->addUnit(unit);
		
			//gen position
			unit->getBattleUnit()->setPosition(randomPoint);
			pBattleLayer->addChild(unit->getUnitGraphic(), 1);//, genZ);
			
			genZ--;
			this->genTime = 0.0f;
			
			this->genUnitType = UT_NONE;
		}
		else
		{
			unit->release();
			unit = NULL;
		}
	}
	this->genTime += _dt;
}

//---------------------------------------------------------------
//---------------------------------------------------------------