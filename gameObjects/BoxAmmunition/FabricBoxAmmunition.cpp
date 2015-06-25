#include "FabricBoxAmmunition.h"
#include "AmmunitionPistol.h"
#include "AmmunitionAutomation.h"
#include "AmmunitionRPG.h"
#include "AmmunitionArtillery.h"
#include "DataLoader.h"

//---------------------------------------------------------------------------------------------------------------------------------
IBoxAmmunition* FabricBoxAmmunition::create(type_weapon _type)
{
	IBoxAmmunition *pBox = NULL;
	CharacteristicsWeapons* weapon = NULL;

	switch (_type)
	{
		case TW_PISTOL:
			weapon = Loader->getCurPistol();
			pBox = AmmunitionPistol::create(weapon->m_countAmmo);
			break;
		case TW_AUTOMATION:
			weapon = Loader->getCurAutomation();
			pBox = AmmunitionAutomation::create(weapon->m_countAmmo);
			break;
		case TW_RPG:
			weapon = Loader->getCurRPG();
			pBox = AmmunitionRPG::create(weapon->m_countAmmo);
			break;
		case TW_ARTILLERY:
			weapon = Loader->getCurArtillery();
			pBox = AmmunitionArtillery::create(weapon->m_countAmmo);
			break;
		default:
			weapon = Loader->getCurPistol();
			pBox = AmmunitionPistol::create(weapon->m_countAmmo);
			break;
	}

    return pBox;
}

IBoxAmmunition* FabricBoxAmmunition::createRandomBox()
{
	IBoxAmmunition *pBox = NULL;
	type_weapon randIdBox = (type_weapon)(rand()%4);
	CharacteristicsWeapons* weapon = NULL;

	switch (randIdBox)
	{
		case TW_PISTOL:
			weapon = Loader->getCurPistol();
			pBox = AmmunitionPistol::create(weapon->m_countAmmo);
			break;
		case TW_AUTOMATION:
			weapon = Loader->getCurAutomation();
			pBox = AmmunitionAutomation::create(weapon->m_countAmmo);
			break;
		case TW_RPG:
			weapon = Loader->getCurRPG();
			pBox = AmmunitionRPG::create(weapon->m_countAmmo);
			break;
		case TW_ARTILLERY:
			weapon = Loader->getCurArtillery();
			pBox = AmmunitionArtillery::create(weapon->m_countAmmo);
			break;
		default:
			weapon = Loader->getCurPistol();
			pBox = AmmunitionPistol::create(weapon->m_countAmmo);
			break;
	}

    return pBox;
}