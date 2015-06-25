#include "Enums.h"
#include "cocos2d.h"
#include "BattleModel.h"

class Weapon
{
public:
	static Weapon*				create();
	
	void						release();

	void						update(float _dt);

private:
	Weapon();
	~Weapon();

	bool						init();

public:
	void						onShot(cocos2d::CCPoint _point);
	void						onMoveShoting(cocos2d::CCPoint _point);
	void						onEndShot();

	void						setSelectedWeapon(type_weapon _type);
	type_weapon					getSelectedWeapon() { return selectedWeapon; };

	CharacteristicsWeapons*		getSelectedWeaponChars() { return selectedWeaponChars; };
	
	void						setBattleModel(BattleModel* _pBattleModel) { pBattleModel = _pBattleModel; };

private:
	void						reloadWeapon(type_weapon _typeWeapon);
	//
	BattleModel*				pBattleModel;
	//
	type_weapon					selectedWeapon;
	CharacteristicsWeapons*		selectedWeaponChars;
	//
	bool						reloadingState;
	//
	bool						canShot;
	float						shotDelay;
	float						reloadDelay;
	//
	float						reloadTimer;
	float						shotTimer;
	//
	float						dt;
};