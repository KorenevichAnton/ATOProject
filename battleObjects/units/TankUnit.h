#ifndef __TankUnit__
#define __TankUnit__

#include "IBattleUnit.h"
#include "BattleObject.h"

class TankUnit : public IBattleUnit
{
public:
	static TankUnit*			create(BattleObject* _pBattleObject);

	void						release();

	void						update(float _dt);

	BattleObject*				getBattleObject() { return pBattleObject; };

private:
	TankUnit();
	~TankUnit();

	bool						init();
	
public:
	void						moveUnit(float _dt);
	
	void						setHP(float _hp) { hp = _hp; };
	float						getHP() { return hp; };

	void						setRadius(float _radius) { radius = _radius; };
	float						getRadius() { return radius; };

private:
	float					hp;
	float					moveSpeed;
	
	float					radius;

	BattleObject*			pBattleObject;
};

#endif //__SimpleSoldierUnit__