#ifndef __IBattleUnit__
#define __IBattleUnit__


#include "cocos2d.h"
#include "MemoryProfiler.h"

class IBattleUnit
{
public:
	IBattleUnit();
	~IBattleUnit();

public:
	virtual void				release() = 0;

	virtual void				moveUnit(float _dt) = 0;

	virtual void				update(float _dt) = 0;

	virtual void				setHP(float _hp) = 0;
	virtual float 				getHP() = 0;
	
	virtual void				setRadius(float _radius) = 0;
	virtual float				getRadius() = 0;

	void						setUnitType(BattleUnitType _unitType) { unitType = _unitType; };
	BattleUnitType const		getUnitType() const { return unitType; };

	void						setPosition(cocos2d::CCPoint _position) { position = _position; };
	cocos2d::CCPoint			getPosition() { return position; }; 

	void						setUnitId(int _id) { id = _id; };
	int							getUnitId() { return id; };

protected:
	BattleUnitType			unitType;
	cocos2d::CCPoint		position;

	int						id;
};

#endif //__IBattleUnit__