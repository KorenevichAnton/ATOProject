#ifndef __SimpleSoldierUnit__
#define __SimpleSoldierUnit__

#include "IBattleUnit.h"
#include "BattleObject.h"

class SimpleSoldierUnit : public IBattleUnit
{
public:
	static SimpleSoldierUnit*	create(BattleObject* _pBattleObject);

	void						release();

	void						update(float _dt);
	
	BattleObject*				getBattleObject() { return pBattleObject; };
	
	void						setHP(float _hp) { hp = _hp; };
	float						getHP() { return hp; };

	void						setRadius(float _radius) { radius = _radius; };
	float						getRadius() { return radius; };

private:
	SimpleSoldierUnit();
	~SimpleSoldierUnit();

	bool						init();

public:
	void						moveUnit(float _dt);

private:
	float					hp;
	float					moveSpeed;
	
	float					radius;

	BattleObject*			pBattleObject;
};

#endif //__SimpleSoldierUnit__