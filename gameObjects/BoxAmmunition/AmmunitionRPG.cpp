#include "AmmunitionRPG.h"
#include "DataLoader.h"

using namespace cocos2d;

//---------------------------------------------------------------------------------------------------------------------------------
AmmunitionRPG::AmmunitionRPG()
{
    
}
//---------------------------------------------------------------------------------------------------------------------------------
AmmunitionRPG::~AmmunitionRPG()
{
	
}
//---------------------------------------------------------------------------------------------------------------------------------
bool AmmunitionRPG::init()
{
	m_box = CCSprite::create("textures/scenes/main/box.png");
	this->addChild(m_box);

	this->m_BackgroundIconAmmo = CCSprite::create("textures/scenes/main/backgroundIcon.png");
	this->m_BackgroundIconAmmo->setVisible(false);
	this->addChild(this->m_BackgroundIconAmmo);

	this->m_IconAmmo = CCSprite::create("textures/scenes/main/ammo/pistol.png");
	this->m_IconAmmo->setVisible(false);
	this->addChild(this->m_IconAmmo);
	
	this->m_lCountAmmo = CCLabelBMFont::create("12", "fonts/days26black.fnt", 40);
	this->m_lCountAmmo->setVisible(false);
	this->addChild(this->m_lCountAmmo);
	m_type = TW_PISTOL;
	
    return true;
}
//---------------------------------------------------------------------------------------------------------------------------------
AmmunitionRPG* AmmunitionRPG::create(int _countAmmo)
{
	AmmunitionRPG *pRet = new AmmunitionRPG();
	pRet->m_CountAmmo = _countAmmo;
	
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }else
	{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
    return pRet;
}


//---------------------------------------------------------------------------------------------------------------------------------
void AmmunitionRPG::increaseAmmo()
{
	Loader->addAmmoPistol(m_CountAmmo);
}
//---------------------------------------------------------------------------------------------------------------------------------