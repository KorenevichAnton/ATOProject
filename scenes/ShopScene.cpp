#include "ShopScene.h"
#include "FabricBoxAmmunition.h"
#include "MainMenuScene.h"
#include "ManagerPurchase.h"
#include "DataLoader.h"

using namespace cocos2d;

ShopScene* ShopScene::pSelf = NULL;

//---------------------------------------------------------------------------------------------------------------------------------
CCScene* ShopScene::scene()
{
    //'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    
    //'layer' is an autorelease object
    ShopScene::pSelf = ShopScene::create();
    scene->addChild( ShopScene::pSelf );

    return scene;
}

//---------------------------------------------------------------------------------------------------------------------------------
ShopScene::ShopScene() : 
	m_myMoney(NULL)
{

}

//---------------------------------------------------------------------------------------------------------------------------------
ShopScene::~ShopScene()
{   
    ShopScene::pSelf = NULL;
}

//---------------------------------------------------------------------------------------------------------------------------------
bool ShopScene::init()
{
    //super init first
    if(!CCLayer::init())
        return false;

    this->initMenu();
	
	this->initBackground();
	this->initInterface();

    this->scheduleUpdate();
    this->setTouchEnabled(true);

    return true;
}

void ShopScene::initInterface()
{
	char buf[50];
	DataLoader* pLoader = Loader;

	m_notEnoughScreen = NotEnoughScreen::create();
	m_notEnoughScreen->setVisible(false);
	m_notEnoughScreen->iniParentScene(this);
	this->addChild(m_notEnoughScreen, 100000);

	CCLayer* scrollLayer = CCLayer::create();
	scrollLayer->setPosition(ccp(0, -80));
	this->addChild(scrollLayer);

	CCSprite* podloshkaCity = CCSprite::create("textures/scenes/shop/podloshka.png");
	podloshkaCity->setPosition(ccp( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.22 ));
	scrollLayer->addChild(podloshkaCity);

	CCSprite* podloshkaPistol = CCSprite::create("textures/scenes/shop/podloshka.png");
	podloshkaPistol->setPosition(ccp( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.52 ));
	scrollLayer->addChild(podloshkaPistol);

	CCSprite* podloshkaAutomatic = CCSprite::create("textures/scenes/shop/podloshka.png");
	podloshkaAutomatic->setPosition(ccp( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 ));
	scrollLayer->addChild(podloshkaAutomatic);
	
	CCSprite* podloshkaRpg = CCSprite::create("textures/scenes/shop/podloshka.png");
	podloshkaRpg->setPosition(ccp( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.9 ));
	scrollLayer->addChild(podloshkaRpg);

	CCSprite* podloshkaArtilery = CCSprite::create("textures/scenes/shop/podloshka.png");
	podloshkaArtilery->setPosition(ccp( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5.3 ));
	scrollLayer->addChild(podloshkaArtilery);

	m_yesNoPurchase = YesNoScreen::create();
	m_yesNoPurchase->setVisible(false);
	this->addChild(m_yesNoPurchase, 100000);

	CCSprite* pistol = CCSprite::create("textures/scenes/main/weapons/pistol_down.png");
	pistol->setPosition(ccp( podloshkaPistol->getContentSize().width / 10, podloshkaPistol->getContentSize().height / 1.5));
	podloshkaPistol->addChild(pistol);

	CCSprite* automatic = CCSprite::create("textures/scenes/main/weapons/automatic_down.png");
	automatic->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 10, podloshkaAutomatic->getContentSize().height / 1.5));
	podloshkaAutomatic->addChild(automatic);

	CCSprite* rpg = CCSprite::create("textures/scenes/main/weapons/rpg_down.png");
	rpg->setPosition(ccp( podloshkaRpg->getContentSize().width / 10, podloshkaRpg->getContentSize().height / 1.5));
	podloshkaRpg->addChild(rpg);
	
	CCSprite* artilery = CCSprite::create("textures/scenes/main/weapons/artilery_down.png");
	artilery->setPosition(ccp( podloshkaArtilery->getContentSize().width / 10, podloshkaArtilery->getContentSize().height / 1.5));
	podloshkaArtilery->addChild(artilery);
	
	sprintf(buf, "%d ", pLoader->getAmmoPistol());
	m_countAmmoPistol = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 40);
	m_countAmmoPistol->setColor(ccWHITE);
	m_countAmmoPistol->setPosition(ccp( podloshkaPistol->getContentSize().width / 12, podloshkaPistol->getContentSize().height / 5));
	podloshkaPistol->addChild(m_countAmmoPistol);

	sprintf(buf, "%d ", pLoader->getAmmoAutomat());
	m_countAmmoAutomatic = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 40);
	m_countAmmoAutomatic->setColor(ccWHITE);
	m_countAmmoAutomatic->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 12, podloshkaAutomatic->getContentSize().height / 5));
	podloshkaAutomatic->addChild(m_countAmmoAutomatic);

	sprintf(buf, "%d ", pLoader->getAmmoRPG());
	m_countAmmoRpg = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 40);
	m_countAmmoRpg->setColor(ccWHITE);
	m_countAmmoRpg->setPosition(ccp( podloshkaRpg->getContentSize().width / 12, podloshkaRpg->getContentSize().height / 5));
	podloshkaRpg->addChild(m_countAmmoRpg);

	sprintf(buf, "%d ", pLoader->getAmmoArtillery());
	m_countAmmoArtilery = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 40);
	m_countAmmoArtilery->setColor(ccWHITE);
	m_countAmmoArtilery->setPosition(ccp( podloshkaArtilery->getContentSize().width / 12, podloshkaArtilery->getContentSize().height / 5));
	podloshkaArtilery->addChild(m_countAmmoArtilery);
	
	CCSprite* iconPowerPistol = CCSprite::create("textures/scenes/shop/iconPower.png");
	iconPowerPistol->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 3, podloshkaAutomatic->getContentSize().height / 1.5));
	podloshkaPistol->addChild(iconPowerPistol);

	CCSprite* iconPowerAutomatic = CCSprite::create("textures/scenes/shop/iconPower.png");
	iconPowerAutomatic->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 3, podloshkaAutomatic->getContentSize().height / 1.5));
	podloshkaAutomatic->addChild(iconPowerAutomatic);

	CCSprite* iconPowerRpg = CCSprite::create("textures/scenes/shop/iconPower.png");
	iconPowerRpg->setPosition(ccp( podloshkaRpg->getContentSize().width / 3, podloshkaRpg->getContentSize().height / 1.5));
	podloshkaRpg->addChild(iconPowerRpg);
	
	CCSprite* iconPowerArtilery = CCSprite::create("textures/scenes/shop/iconPower.png");
	iconPowerArtilery->setPosition(ccp( podloshkaArtilery->getContentSize().width / 3, podloshkaArtilery->getContentSize().height / 1.5));
	podloshkaArtilery->addChild(iconPowerArtilery);

	CCSprite* iconSpeedPistol = CCSprite::create("textures/scenes/shop/iconSpeed.png");
	iconSpeedPistol->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 2.1, podloshkaAutomatic->getContentSize().height / 1.5));
	podloshkaPistol->addChild(iconSpeedPistol);

	CCSprite* iconSpeedAutomatic = CCSprite::create("textures/scenes/shop/iconSpeed.png");
	iconSpeedAutomatic->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 2.1, podloshkaAutomatic->getContentSize().height / 1.5));
	podloshkaAutomatic->addChild(iconSpeedAutomatic);

	CCSprite* iconSpeedRpg = CCSprite::create("textures/scenes/shop/iconSpeed.png");
	iconSpeedRpg->setPosition(ccp( podloshkaRpg->getContentSize().width / 2.1, podloshkaRpg->getContentSize().height / 1.5));
	podloshkaRpg->addChild(iconSpeedRpg);
	
	CCSprite* iconSpeedArtilery = CCSprite::create("textures/scenes/shop/iconSpeed.png");
	iconSpeedArtilery->setPosition(ccp( podloshkaArtilery->getContentSize().width / 2.1, podloshkaArtilery->getContentSize().height / 1.5));
	podloshkaArtilery->addChild(iconSpeedArtilery);

	CCSprite* iconCountAmmoPistol = CCSprite::create("textures/scenes/shop/iconCountAmmo.png");
	iconCountAmmoPistol->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 1.6, podloshkaAutomatic->getContentSize().height / 1.5));
	podloshkaPistol->addChild(iconCountAmmoPistol);

	CCSprite* iconCountAmmoAutomatic = CCSprite::create("textures/scenes/shop/iconCountAmmo.png");
	iconCountAmmoAutomatic->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 1.6, podloshkaAutomatic->getContentSize().height / 1.5));
	podloshkaAutomatic->addChild(iconCountAmmoAutomatic);

	CCSprite* iconCountAmmoRpg = CCSprite::create("textures/scenes/shop/iconCountAmmo.png");
	iconCountAmmoRpg->setPosition(ccp( podloshkaRpg->getContentSize().width / 1.6, podloshkaRpg->getContentSize().height / 1.5));
	podloshkaRpg->addChild(iconCountAmmoRpg);
	
	CCSprite* iconCountAmmoArtilery = CCSprite::create("textures/scenes/shop/iconCountAmmo.png");
	iconCountAmmoArtilery->setPosition(ccp( podloshkaArtilery->getContentSize().width / 1.6, podloshkaArtilery->getContentSize().height / 1.5));
	podloshkaArtilery->addChild(iconCountAmmoArtilery);

	CCSprite* iconRadiusPistol = CCSprite::create("textures/scenes/shop/iconRadius.png");
	iconRadiusPistol->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 1.3, podloshkaAutomatic->getContentSize().height / 1.5));
	podloshkaPistol->addChild(iconRadiusPistol);

	CCSprite* iconRadiusAutomatic = CCSprite::create("textures/scenes/shop/iconRadius.png");
	iconRadiusAutomatic->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 1.3, podloshkaAutomatic->getContentSize().height / 1.5));
	podloshkaAutomatic->addChild(iconRadiusAutomatic);

	CCSprite* iconRadiusRpg = CCSprite::create("textures/scenes/shop/iconRadius.png");
	iconRadiusRpg->setPosition(ccp( podloshkaRpg->getContentSize().width / 1.3, podloshkaRpg->getContentSize().height / 1.5));
	podloshkaRpg->addChild(iconRadiusRpg);
	
	CCSprite* iconRadiusArtilery = CCSprite::create("textures/scenes/shop/iconRadius.png");
	iconRadiusArtilery->setPosition(ccp( podloshkaArtilery->getContentSize().width / 1.3, podloshkaArtilery->getContentSize().height / 1.5));
	podloshkaArtilery->addChild(iconRadiusArtilery);


	CharacteristicsWeapons*	drawCharacterPistol = pLoader->getNextPistol();
	if(drawCharacterPistol == NULL)
		drawCharacterPistol = pLoader->getCurPistol();
	if(drawCharacterPistol)
	{
		sprintf(buf, "%d ", drawCharacterPistol->m_damage);
		m_powerPistol = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_powerPistol->setColor(ccWHITE);
		m_powerPistol->setPosition(ccp( podloshkaPistol->getContentSize().width / 3, podloshkaPistol->getContentSize().height / 3));
		podloshkaPistol->addChild(m_powerPistol);

		sprintf(buf, "%d ", drawCharacterPistol->m_speed);
		m_speedPistol = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_speedPistol->setColor(ccWHITE);
		m_speedPistol->setPosition(ccp( podloshkaPistol->getContentSize().width / 2.1, podloshkaPistol->getContentSize().height / 3));
		podloshkaPistol->addChild(m_speedPistol);

		sprintf(buf, "%d ", drawCharacterPistol->m_countAmmo);
		m_countAmmoCagePistol = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_countAmmoCagePistol->setColor(ccWHITE);
		m_countAmmoCagePistol->setPosition(ccp( podloshkaPistol->getContentSize().width / 1.6, podloshkaPistol->getContentSize().height / 3));
		podloshkaPistol->addChild(m_countAmmoCagePistol);

		sprintf(buf, "%d ", drawCharacterPistol->m_radius);
		m_radiusPistol = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_radiusPistol->setColor(ccWHITE);
		m_radiusPistol->setPosition(ccp( podloshkaPistol->getContentSize().width / 1.3, podloshkaPistol->getContentSize().height / 3));
		podloshkaPistol->addChild(m_radiusPistol);
	}

	CharacteristicsWeapons* drawCharacterAutomation = pLoader->getNextAutomation();
	if(drawCharacterAutomation == NULL)
		drawCharacterAutomation = pLoader->getCurAutomation();

	if(drawCharacterAutomation)
	{
		sprintf(buf, "%d ", drawCharacterAutomation->m_damage);
		m_powerAutomatic = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_powerAutomatic->setColor(ccWHITE);
		m_powerAutomatic->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 3, podloshkaAutomatic->getContentSize().height / 3));
		podloshkaAutomatic->addChild(m_powerAutomatic);

		sprintf(buf, "%d ", drawCharacterAutomation->m_speed);
		m_speedAutomatic = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_speedAutomatic->setColor(ccWHITE);
		m_speedAutomatic->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 2.1, podloshkaAutomatic->getContentSize().height / 3));
		podloshkaAutomatic->addChild(m_speedAutomatic);

		sprintf(buf, "%d ", drawCharacterAutomation->m_countAmmo);
		m_countAmmoCageAutomatic = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_countAmmoCageAutomatic->setColor(ccWHITE);
		m_countAmmoCageAutomatic->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 1.6, podloshkaAutomatic->getContentSize().height / 3));
		podloshkaAutomatic->addChild(m_countAmmoCageAutomatic);

		sprintf(buf, "%d", drawCharacterAutomation->m_radius);
		m_radiusAutomatic = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_radiusAutomatic->setColor(ccWHITE);
		m_radiusAutomatic->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 1.3, podloshkaAutomatic->getContentSize().height / 3));
		podloshkaAutomatic->addChild(m_radiusAutomatic);
	}

	CharacteristicsWeapons*	drawCharacterRPG = pLoader->getNextRPG();
	if(drawCharacterRPG == NULL)
		drawCharacterRPG = pLoader->getCurRPG();
	
	if(drawCharacterRPG)
	{
		sprintf(buf, "%d ", drawCharacterRPG->m_damage);
		m_powerRpg = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_powerRpg->setColor(ccWHITE);
		m_powerRpg->setPosition(ccp( podloshkaRpg->getContentSize().width / 3, podloshkaRpg->getContentSize().height / 3));
		podloshkaRpg->addChild(m_powerRpg);

		sprintf(buf, "%d ", drawCharacterRPG->m_speed);
		m_speedRpg = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_speedRpg->setColor(ccWHITE);
		m_speedRpg->setPosition(ccp( podloshkaRpg->getContentSize().width / 2.1, podloshkaRpg->getContentSize().height / 3));
		podloshkaRpg->addChild(m_speedRpg);

		sprintf(buf, "%d ", drawCharacterRPG->m_countAmmo);
		m_countAmmoCageRpg = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_countAmmoCageRpg->setColor(ccWHITE);
		m_countAmmoCageRpg->setPosition(ccp( podloshkaRpg->getContentSize().width / 1.6, podloshkaRpg->getContentSize().height / 3));
		podloshkaRpg->addChild(m_countAmmoCageRpg);

		sprintf(buf, "%d ", drawCharacterRPG->m_radius);
		m_radiusRpg = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_radiusRpg->setColor(ccWHITE);
		m_radiusRpg->setPosition(ccp( podloshkaRpg->getContentSize().width / 1.3, podloshkaRpg->getContentSize().height / 3));
		podloshkaRpg->addChild(m_radiusRpg);
	}

	CharacteristicsWeapons*	drawCharacterArtilery = pLoader->getNextArtillery();
	if(drawCharacterArtilery == NULL)
		drawCharacterArtilery = pLoader->getCurArtillery();
	
	if(drawCharacterArtilery)
	{
		sprintf(buf, "%d ", drawCharacterArtilery->m_damage);
		m_powerArtilery = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_powerArtilery->setColor(ccWHITE);
		m_powerArtilery->setPosition(ccp( podloshkaArtilery->getContentSize().width / 3, podloshkaArtilery->getContentSize().height / 3));
		podloshkaArtilery->addChild(m_powerArtilery);

		sprintf(buf, "%d ", drawCharacterArtilery->m_speed);
		m_speedArtilery = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_speedArtilery->setColor(ccWHITE);
		m_speedArtilery->setPosition(ccp( podloshkaArtilery->getContentSize().width / 2.1, podloshkaArtilery->getContentSize().height / 3));
		podloshkaArtilery->addChild(m_speedArtilery);

		sprintf(buf, "%d ", drawCharacterArtilery->m_countAmmo);
		m_countAmmoCageArtilery = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_countAmmoCageArtilery->setColor(ccWHITE);
		m_countAmmoCageArtilery->setPosition(ccp( podloshkaArtilery->getContentSize().width / 1.6, podloshkaArtilery->getContentSize().height / 3));
		podloshkaArtilery->addChild(m_countAmmoCageArtilery);

		sprintf(buf, "%d ", drawCharacterArtilery->m_radius);
		m_radiusArtilery = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 45);
		m_radiusArtilery->setColor(ccWHITE);
		m_radiusArtilery->setPosition(ccp( podloshkaArtilery->getContentSize().width / 1.3, podloshkaArtilery->getContentSize().height / 3));
		podloshkaArtilery->addChild(m_radiusArtilery);

	}

	this->upgradePistol = CCMenuItemImage::create("textures/scenes/shop/upgrade.png", "textures/scenes/shop/upgradeDown.png", this, menu_selector(ShopScene::onUpgradePistol));
	this->upgradePistol->setPosition(ccp( SCREEN_WIDTH / 1.12, SCREEN_HEIGHT / 1.8));
	m_menuBtn->addChild(this->upgradePistol);
	if(pLoader->getNextPistol() == NULL)
		this->upgradePistol->setVisible(false);

	this->upgradeAutomatic = CCMenuItemImage::create("textures/scenes/shop/upgrade.png", "textures/scenes/shop/upgradeDown.png", this, menu_selector(ShopScene::onUpgradeAutomatic));
	this->upgradeAutomatic->setPosition(ccp( SCREEN_WIDTH / 1.12, SCREEN_HEIGHT / 2.5));
	m_menuBtn->addChild(this->upgradeAutomatic);
	if(pLoader->getNextAutomation() == NULL)
		this->upgradeAutomatic->setVisible(false);
	
	if(pLoader->getNextCity())
		sprintf(buf, "%s ", pLoader->getNextCity()->m_nameCity);
	else
		sprintf(buf, "%s ", pLoader->getCurCity()->m_nameCity);

	m_nameNextCity = CCLabelTTF::create(buf, "Arial", 40);
	m_nameNextCity->setPosition(ccp(podloshkaCity->getContentSize().width / 2, podloshkaCity->getContentSize().height / 1.5));
	podloshkaCity->addChild(m_nameNextCity);

	this->upgradeRpg = CCMenuItemImage::create("textures/scenes/shop/upgrade.png", "textures/scenes/shop/upgradeDown.png", this, menu_selector(ShopScene::onUpgradeRpg));
	this->upgradeRpg->setPosition(ccp( SCREEN_WIDTH / 1.12, SCREEN_HEIGHT / 4.1));
	m_menuBtn->addChild(this->upgradeRpg);
	if(pLoader->getNextRPG() == NULL)
		this->upgradeRpg->setVisible(false);

	this->upgradeArtilery = CCMenuItemImage::create("textures/scenes/shop/upgrade.png", "textures/scenes/shop/upgradeDown.png", this, menu_selector(ShopScene::onUpgradeArtilery));
	this->upgradeArtilery->setPosition(ccp( SCREEN_WIDTH / 1.12, SCREEN_HEIGHT / 12));
	m_menuBtn->addChild(this->upgradeArtilery);
	if(pLoader->getNextArtillery() == NULL)
		this->upgradeArtilery->setVisible(false);

	this->m_upgradeCity = CCMenuItemImage::create("textures/scenes/shop/upgrade.png", "textures/scenes/shop/upgradeDown.png", this, menu_selector(ShopScene::onUpgradeArtilery));
	this->m_upgradeCity->setPosition(ccp( SCREEN_WIDTH / 1.12, SCREEN_HEIGHT / 12));
	m_menuBtn->addChild(this->m_upgradeCity);
	if(pLoader->getNextCity() == NULL)
		this->m_upgradeCity->setVisible(false);


	if(pLoader->getNextCity())
		sprintf(buf, "%d ", pLoader->getNextCity()->m_price);
	else
		strcpy(buf, " ");

	m_priceUpgradeCity = CCLabelTTF::create(buf, "Arial", 40);
	m_priceUpgradeCity->setColor(ccWHITE);
	m_priceUpgradeCity->setPosition(ccp( podloshkaCity->getContentSize().width / 2, podloshkaCity->getContentSize().height / 2.5));
	podloshkaCity->addChild(m_priceUpgradeCity);
	
	sprintf(buf, "%d ", pLoader->getNextPistol()->m_price);
	m_priceUpgradePistol = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 40);
	m_priceUpgradePistol->setColor(ccWHITE);
	m_priceUpgradePistol->setPosition(ccp( podloshkaPistol->getContentSize().width / 1.1, podloshkaPistol->getContentSize().height / 1.25));
	podloshkaPistol->addChild(m_priceUpgradePistol);

	sprintf(buf, "%d ", pLoader->getNextAutomation()->m_price);
	m_priceUpgradeAutomatic = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 40);
	m_priceUpgradeAutomatic->setColor(ccWHITE);
	m_priceUpgradeAutomatic->setPosition(ccp( podloshkaAutomatic->getContentSize().width / 1.1, podloshkaAutomatic->getContentSize().height / 1.25));
	podloshkaAutomatic->addChild(m_priceUpgradeAutomatic);

	sprintf(buf, "%d ", pLoader->getNextRPG()->m_price);
	m_priceUpgradeRpg = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 40);
	m_priceUpgradeRpg->setColor(ccWHITE);
	m_priceUpgradeRpg->setPosition(ccp( podloshkaRpg->getContentSize().width / 1.1, podloshkaRpg->getContentSize().height / 1.25));
	podloshkaRpg->addChild(m_priceUpgradeRpg);

	sprintf(buf, "%d ", pLoader->getNextArtillery()->m_price);
	m_priceUpgradeArtilery = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 40);
	m_priceUpgradeArtilery->setColor(ccWHITE);
	m_priceUpgradeArtilery->setPosition(ccp( podloshkaArtilery->getContentSize().width / 1.1, podloshkaArtilery->getContentSize().height / 1.25));
	podloshkaArtilery->addChild(m_priceUpgradeArtilery);

	CCMenuItemImage* addAmmoPistol	= CCMenuItemImage::create("textures/scenes/shop/addAmmo.png", "textures/scenes/shop/addAmmo.png", this, menu_selector(ShopScene::onAddAmmoPistol));
	addAmmoPistol->setPosition(ccp( SCREEN_WIDTH / 5, SCREEN_HEIGHT / 1.8));
	m_menuBtn->addChild(addAmmoPistol);

	CCMenuItemImage* addAmmoAutomatic = CCMenuItemImage::create("textures/scenes/shop/addAmmo.png",	 "textures/scenes/shop/addAmmo.png", this, menu_selector(ShopScene::onAddAmmoAutomatic));
	addAmmoAutomatic->setPosition(ccp( SCREEN_WIDTH / 5, SCREEN_HEIGHT / 2.55));
	m_menuBtn->addChild(addAmmoAutomatic);

	CCMenuItemImage* addAmmoRpg = CCMenuItemImage::create("textures/scenes/shop/addAmmo.png", "textures/scenes/shop/addAmmo.png", this, menu_selector(ShopScene::onAddAmmoRpg));
	addAmmoRpg->setPosition(ccp( SCREEN_WIDTH / 5, SCREEN_HEIGHT / 4.1));
	m_menuBtn->addChild(addAmmoRpg);

	CCMenuItemImage* addAmmoArtilery = CCMenuItemImage::create("textures/scenes/shop/addAmmo.png", "textures/scenes/shop/addAmmo.png", this, menu_selector(ShopScene::onAddAmmoArtilery));
	addAmmoArtilery->setPosition(ccp( SCREEN_WIDTH / 5, SCREEN_HEIGHT / 12));
	m_menuBtn->addChild(addAmmoArtilery);

	CCMenuItemImage* addMoney = CCMenuItemImage::create("textures/scenes/shop/addMoney.png", "textures/scenes/shop/addMoney.png", this, menu_selector(ShopScene::onAddMoney));
	addMoney->setPosition(ccp( SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 1.1 ));
	m_menuBtn->addChild(addMoney);


}

void ShopScene::onMainMenu(CCObject* pSender)
{
	Loader->saveAllData();
	CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
}

void ShopScene::onAddAmmoPistol(CCObject* pSender)
{

}
	
void ShopScene::onAddAmmoAutomatic(CCObject* pSender)
{

}
	
void  ShopScene::onAddAmmoRpg(CCObject* pSender)
{

}
	
void  ShopScene::onAddAmmoArtilery(CCObject* pSender)
{

}

void  ShopScene::onAddMoney(CCObject* pSender)
{

}

void ShopScene::onUpgradePistol(CCObject* pSender)
{
	ManagerPurchase* pPurchase = ManagerPurchase::sharedInstance();
	DataLoader* pLoader = Loader;
	CharacteristicsWeapons* upWeapon = pLoader->getNextPistol();

	if(upWeapon->m_id > 0 && pPurchase->getMoney() >= upWeapon->m_price)
	{
		char buf[50];
		sprintf(buf, "Buy for %d ?", upWeapon->m_price);
		m_yesNoPurchase->setDescription(buf);
		m_yesNoPurchase->setStateOnOk(SP_PISTOL, this);
		m_yesNoPurchase->show();
	}else
		m_notEnoughScreen->show();
}

void ShopScene::onUpgradeAutomatic(CCObject* pSender)
{
	ManagerPurchase* pPurchase = ManagerPurchase::sharedInstance();
	DataLoader* pLoader = Loader;
	CharacteristicsWeapons* upWeapon = pLoader->getNextAutomation();

	if(upWeapon->m_id > 0 && pPurchase->getMoney() >= upWeapon->m_price)
	{
		char buf[50];
		sprintf(buf, "Buy for %d ?", upWeapon->m_price);
		m_yesNoPurchase->setDescription(buf);
		m_yesNoPurchase->setStateOnOk(SP_AUTOMATON, this);
		m_yesNoPurchase->show();
	}else
		m_notEnoughScreen->show();
}
	
void  ShopScene::onUpgradeRpg(CCObject* pSender)
{
	ManagerPurchase* pPurchase = ManagerPurchase::sharedInstance();
	DataLoader* pLoader = Loader;
	CharacteristicsWeapons* upWeapon = pLoader->getNextRPG();

	if(upWeapon->m_id > 0 && pPurchase->getMoney() >= upWeapon->m_price)
	{
		char buf[50];
		sprintf(buf, "Buy for %d ?", upWeapon->m_price);
		m_yesNoPurchase->setDescription(buf);
		m_yesNoPurchase->setStateOnOk(SP_RPG, this);
		m_yesNoPurchase->show();
	}else
		m_notEnoughScreen->show();
}

void  ShopScene::onUpgradeArtilery(CCObject* pSender)
{
	ManagerPurchase* pPurchase = ManagerPurchase::sharedInstance();
	DataLoader* pLoader = Loader;
	CharacteristicsWeapons* upWeapon = pLoader->getNextArtillery();

	if(upWeapon->m_id > 0 && pPurchase->getMoney() >= upWeapon->m_price)
	{
		char buf[50];
		sprintf(buf, "Buy for %d ?", upWeapon->m_price);
		m_yesNoPurchase->setDescription(buf);
		m_yesNoPurchase->setStateOnOk(SP_ARTILERY, this);
		m_yesNoPurchase->show();
	}else
		m_notEnoughScreen->show();
}

void ShopScene::initBackground()
{
	// add background image	
    CCSprite* bg = CCSprite::create("textures/scenes/main/bg/1.jpg");
	bg->setAnchorPoint(CCPointZero);
    bg->setPosition(ccp(0, SCREEN_HEIGHT / 2));
    this->addChild(bg);


	bg = CCSprite::create("textures/scenes/main/bg/2.jpg");
	bg->setAnchorPoint(CCPointZero);
    bg->setPosition(ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    this->addChild(bg);
    //
	
	bg = CCSprite::create("textures/scenes/main/bg/3.jpg");
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(CCPointZero);
    this->addChild(bg);
    //

	bg = CCSprite::create("textures/scenes/main/bg/4.jpg");
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(ccp(SCREEN_WIDTH / 2, 0));
    this->addChild(bg);
    //

	char buf[50];
	sprintf(buf, "%d ", ManagerPurchase::sharedInstance()->getMoney());
	m_myMoney = CCLabelTTF::create(buf, "Arial", 40);
	m_myMoney->setColor(ccWHITE);
	m_myMoney->setPosition(ccp( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.1));
	this->addChild(m_myMoney);
}

//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::initMenu()
{
	m_menuBtn = CCMenu::create();
	m_menuBtn->setPosition(CCPointZero);
	this->addChild(m_menuBtn, 100);

	CCMenuItemImage* btnMainMenu = CCMenuItemImage::create("textures/scenes/shop/btnMainMenu.png", "textures/scenes/shop/btnMainMenu.png", this, menu_selector(ShopScene::onMainMenu));
	btnMainMenu->setPosition(ccp( SCREEN_WIDTH / 10, SCREEN_HEIGHT / 1.1));
	m_menuBtn->addChild(btnMainMenu);
}

//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::onEnter()
{
    CCLayer::onEnter();
    CCLOG("ShopScene::onEnter");
}
//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::onExit()
{
    CCLayer::onExit();
    CCLOG("ShopScene::onExit");
}
//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::update(float _dt)
{
	char buf[50];

	DataLoader* pLoader = DataLoader::sharedInstance();

	sprintf(buf, "%d ", pLoader->getAmmoPistol());
	m_countAmmoPistol->setString(buf);

	sprintf(buf, "%d ", pLoader->getAmmoAutomat());
	m_countAmmoAutomatic->setString(buf);

	sprintf(buf, "%d ", pLoader->getAmmoRPG());
	m_countAmmoRpg->setString(buf);

	sprintf(buf, "%d ", pLoader->getAmmoArtillery());
	m_countAmmoArtilery->setString(buf);

	sprintf(buf, "%d ", ManagerPurchase::sharedInstance()->getMoney());
	m_myMoney->setString(buf);
}
//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::updateLabeUpgradeCity()
{
	DataLoader* pLoader = Loader;

	city* tCity = pLoader->getNextCity();
	if(tCity)
	{
		char buf[50];

		sprintf(buf, "%d ", tCity->m_price);
		this->m_priceUpgradeCity->setString(buf);

		this->m_upgradeCity->setVisible(true);
	}else
	{
		tCity = pLoader->getCurCity();
		if(tCity)
			this->m_nameNextCity->setString(tCity->m_nameCity);


		this->m_priceUpgradeCity->setVisible(false);
		this->m_upgradeCity->setVisible(false);
	}
}
//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::updateLabeUpgradePistol()
{
	CharacteristicsWeapons* tWeapon = Loader->getNextPistol();

	if(tWeapon)
	{
		char buf[50];

		sprintf(buf, "%d ", tWeapon->m_price);
		m_priceUpgradePistol->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_damage);
		m_powerPistol->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_speed);
		m_radiusPistol->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_countAmmo);
		m_countAmmoCagePistol->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_radius);
		m_radiusPistol->setString(buf);
	}else
	{
		upgradePistol->setVisible(false);
		m_priceUpgradePistol->setVisible(false);
	}
}
//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::updateLabeUpgradeAutomaton()
{
	CharacteristicsWeapons* tWeapon = Loader->getNextAutomation();

	if(tWeapon)
	{
		char buf[50];

		sprintf(buf, "%d ", tWeapon->m_price);
		m_priceUpgradeAutomatic->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_damage);
		m_powerAutomatic->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_speed);
		m_speedAutomatic->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_countAmmo);
		m_countAmmoCageAutomatic->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_radius);
		m_radiusAutomatic->setString(buf);
	}else
	{
		upgradeAutomatic->setVisible(false);
		m_priceUpgradeAutomatic->setVisible(false);
	}
}
//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::updateLabeUpgradeRpg()
{
	CharacteristicsWeapons* tWeapon = Loader->getNextRPG();

	if(tWeapon)
	{
		char buf[50];

		sprintf(buf, "%d ", tWeapon->m_price);
		m_priceUpgradeRpg->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_damage);
		m_powerRpg->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_speed);
		m_speedRpg->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_countAmmo);
		m_countAmmoCageRpg->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_radius);
		m_radiusRpg->setString(buf);
	}else
	{
		upgradeRpg->setVisible(false);
		m_priceUpgradeRpg->setVisible(false);
	}
}
//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::updateLabeUpgradeArtilery()
{
	CharacteristicsWeapons* tWeapon = Loader->getNextArtillery();

	if(tWeapon)
	{
		char buf[50];

		sprintf(buf, "%d ", tWeapon->m_price);
		m_priceUpgradeArtilery->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_damage);
		m_powerArtilery->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_speed);
		m_speedArtilery->setString(buf);

		sprintf(buf, "%d ", tWeapon->m_countAmmo);
		m_countAmmoCageArtilery->setString(buf);
	
		sprintf(buf, "%d ", tWeapon->m_radius);
		m_radiusArtilery->setString(buf);
	}else
	{
		upgradeArtilery->setVisible(false);
		m_priceUpgradeArtilery->setVisible(false);
	}
}
//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::ccTouchesBegan(CCSet* _touches, CCEvent* _event)
{
	CCTouch* touch = NULL;
	touch = dynamic_cast<CCTouch*>(_touches->anyObject());
}
//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::ccTouchesEnded(CCSet* _touches, CCEvent* _event)
{

}
//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::ccTouchesMoved(CCSet* _touches, CCEvent* _event)
{
	CCTouch* touch = NULL;
	touch = dynamic_cast<CCTouch*>(_touches->anyObject());
	
}
//---------------------------------------------------------------------------------------------------------------------------------
void ShopScene::ccTouchesCancelled(CCSet* _touches, CCEvent* _event)
{
	
}