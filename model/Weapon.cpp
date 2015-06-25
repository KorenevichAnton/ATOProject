#include "Weapon.h"
#include "MemoryProfiler.h"
#include "BattleObject.h"
#include <vector>
#include "DataLoader.h"

using namespace cocos2d;
using namespace std;

//----------------------------------------------------------------
Weapon* Weapon::create()
{
	Weapon *pWeapon = new Weapon();
	if(pWeapon && pWeapon->init())
	{
		return pWeapon;
	}
	delete pWeapon;
	return NULL;
}

//----------------------------------------------------------------
Weapon::Weapon():
	selectedWeapon(TW_PISTOL),
	selectedWeaponChars(Loader->getCurPistol()),
	pBattleModel(NULL),
	shotDelay(1.0f),
	reloadDelay(5.0f),
	shotTimer(0.0f),
	reloadTimer(0.0f),
	reloadingState(false),
	dt(0.0f)
{

}

//----------------------------------------------------------------
Weapon::~Weapon()
{

}

//----------------------------------------------------------------
void Weapon::release()
{
	delete this;
}

//----------------------------------------------------------------
bool Weapon::init()
{
	return true;
}

//----------------------------------------------------------------
void Weapon::setSelectedWeapon(type_weapon _type)
{
	this->shotDelay = 1.0;
	this->reloadDelay = 5.0;
	//
	this->selectedWeapon = _type;
	switch (this->selectedWeapon)
	{
	case TW_PISTOL:
		this->selectedWeaponChars = Loader->getCurPistol();		
		break;
	case TW_AUTOMATION:
		this->selectedWeaponChars = Loader->getCurAutomation();
		break;
	case TW_RPG:
		this->selectedWeaponChars = Loader->getCurRPG();
		break;
	case TW_ARTILLERY:
		this->selectedWeaponChars = Loader->getCurArtillery();
		break;
	default:	
		break;
	}
	//
	this->shotDelay = this->shotDelay / this->getSelectedWeaponChars()->m_speed;
}

//----------------------------------------------------------------
void Weapon::update(float _dt)
{
	if(Loader->getCurPistol()->m_curAmmo == 0)
		Loader->getCurPistol()->m_reloadingState = true;
	if(Loader->getCurAutomation()->m_curAmmo == 0)
		Loader->getCurAutomation()->m_reloadingState = true;
	if(Loader->getCurRPG()->m_curAmmo == 0)
		Loader->getCurRPG()->m_reloadingState = true;
	if(Loader->getCurArtillery()->m_curAmmo == 0)
		Loader->getCurArtillery()->m_reloadingState = true;

	//Reloading timer
	if(Loader->getCurPistol()->m_reloadingState)
	{
		Loader->getCurPistol()->m_reloadTimer += _dt;
		if(Loader->getCurPistol()->m_reloadTimer >= this->reloadDelay - 3 / Loader->getCurPistol()->m_speed)
		{
			this->reloadWeapon(TW_PISTOL);
			Loader->getCurPistol()->m_reloadTimer = 0;
			Loader->getCurPistol()->m_reloadingState = false;
		}
	}
	//
	if(Loader->getCurAutomation()->m_reloadingState)
	{
		Loader->getCurAutomation()->m_reloadTimer += _dt;
		if(Loader->getCurAutomation()->m_reloadTimer >= this->reloadDelay / Loader->getCurAutomation()->m_speed)
		{
			this->reloadWeapon(TW_AUTOMATION);
			Loader->getCurAutomation()->m_reloadTimer = 0;
			Loader->getCurAutomation()->m_reloadingState = false;
		}
	}
	//
	if(Loader->getCurRPG()->m_reloadingState)
	{
		Loader->getCurRPG()->m_reloadTimer += _dt;
		if(Loader->getCurRPG()->m_reloadTimer >= this->reloadDelay / Loader->getCurRPG()->m_speed)
		{
			this->reloadWeapon(TW_RPG);
			Loader->getCurRPG()->m_reloadTimer = 0;
			Loader->getCurRPG()->m_reloadingState = false;
		}
	}
	//
	if(Loader->getCurArtillery()->m_reloadingState)
	{
		Loader->getCurArtillery()->m_reloadTimer += _dt;
		if(Loader->getCurArtillery()->m_reloadTimer >= this->reloadDelay / Loader->getCurArtillery()->m_speed)
		{
			this->reloadWeapon(TW_ARTILLERY);
			Loader->getCurArtillery()->m_reloadTimer = 0;
			Loader->getCurArtillery()->m_reloadingState = false;
		}
	}

	this->dt = _dt;
}

//----------------------------------------------------------------
void Weapon::onShot(CCPoint _point)
{
	if(!this->reloadingState)
	{
		//start shoting with multi-point weapon
		//this->canShot = true;
		
		if(selectedWeapon == TW_AUTOMATION || selectedWeapon == TW_ARTILLERY)
		{
			this->onMoveShoting(_point);
			this->canShot = true;
			return;
		}
		//
		if(this->getSelectedWeaponChars()->m_curAmmo > 0)
		{
			//make shot one-point shot
			std::vector<BattleObject*> battleObjects = pBattleModel->getBattleUnits();
			for(vector<BattleObject*>::iterator it = battleObjects.begin() ; it < battleObjects.end() ; it++)
			{
				float distance = ccpDistance((*it)->getBattleUnit()->getPosition(), _point);
				if(fabs(distance) < selectedWeaponChars->m_radius + (*it)->getBattleUnit()->getRadius())
				{
					(*it)->getBattleUnit()->setHP((*it)->getBattleUnit()->getHP() - selectedWeaponChars->m_damage);
				}
			}	
			//decr ammo
			selectedWeaponChars->m_curAmmo--;
		}
	}
}

//----------------------------------------------------------------
void Weapon::onEndShot()
{
	this->canShot = false;
}

//----------------------------------------------------------------
void Weapon::onMoveShoting(CCPoint _point)
{
	this->shotTimer += this->dt;
	if(this->shotTimer > this->shotDelay / this->getSelectedWeaponChars()->m_speed)
	{
		this->shotTimer = 0;
		if((this->selectedWeapon == TW_AUTOMATION || 
			this->selectedWeapon == TW_ARTILLERY) && 
			canShot == true &&
			this->selectedWeaponChars->m_curAmmo > 0)
		{
			std::vector<BattleObject*> battleObjects = pBattleModel->getBattleUnits();
			for(vector<BattleObject*>::iterator it = battleObjects.begin() ; it < battleObjects.end() ; it++)
			{
				float distance = ccpDistance((*it)->getBattleUnit()->getPosition(), _point);
				if(fabs(distance) < selectedWeaponChars->m_radius + (*it)->getBattleUnit()->getRadius())
				{
					(*it)->getBattleUnit()->setHP((*it)->getBattleUnit()->getHP() - selectedWeaponChars->m_damage);
				}
			}	
			selectedWeaponChars->m_curAmmo--;
		}
	}
}

//----------------------------------------------------------------
void Weapon::reloadWeapon(type_weapon _typeWeapon)
{
	switch (_typeWeapon)
	{
	case TW_PISTOL:
		for(int i = 0 ; i < Loader->getCurPistol()->m_countAmmo ; i++)
		{
			if(Loader->getAmmoPistol() > 0)
			{
				Loader->addAmmoPistol(-1);
				Loader->getCurPistol()->m_curAmmo++;
			}
		}
		break;
	case TW_AUTOMATION:
		for(int i = 0 ; i < Loader->getCurAutomation()->m_countAmmo ; i++)
		{
			if(Loader->getAmmoAutomat() > 0)
			{
				Loader->addAmmoAutomat(-1);
				Loader->getCurAutomation()->m_curAmmo++;
			}
		}
		break;
	case TW_RPG:
		for(int i = 0 ; i < Loader->getCurRPG()->m_countAmmo ; i++)
		{
			if(Loader->getAmmoRPG() > 0)
			{
				Loader->addAmmoRPG(-1);
				Loader->getCurRPG()->m_curAmmo++;
			}
		}
		break;
	case TW_ARTILLERY:
		for(int i = 0 ; i < Loader->getCurArtillery()->m_countAmmo ; i++)
		{
			if(Loader->getAmmoArtillery() > 0)
			{
				Loader->addAmmoArtillery(-1);
				Loader->getCurArtillery()->m_curAmmo++;
			}
		}
		break;
	default:	
		break;
	}
}

//----------------------------------------------------------------