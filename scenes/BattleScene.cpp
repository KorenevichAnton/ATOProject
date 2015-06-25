#include "BattleScene.h"
#include "BattleObject.h"
#include "BattleUnitFactory.h"
#include "MemoryProfiler.h"
#include <vector>
#include "MainMenuScene.h"
#include "DataLoader.h"
using namespace std;
using namespace cocos2d;

BattleScene *BattleScene::pSelf;

//----------------------------------------------------------------
CCScene* BattleScene::scene()
{
	CCScene* scene = CCScene::create();
	
	BattleScene* layer = BattleScene::create();
	BattleScene::pSelf = layer;
	scene->addChild( layer );

	BattleScene::pSelf->pDebugScreen = DebugDrawScreen::create();
    scene->addChild( BattleScene::pSelf->pDebugScreen );

	BattleScene::pSelf->battleLayer = CCLayer::create();
	scene->addChild(BattleScene::pSelf->battleLayer);

	return scene;
}

//----------------------------------------------------------------
BattleScene::BattleScene():
	pBattleModel(NULL),
	pDebugScreen(NULL),
	weaponSelection(NULL),
	pistolMenuItem(NULL),
	automaticMenuItem(NULL),
	rpgMenuItem(NULL),
	artilleryMenuItem(NULL),
	pWeapon(NULL),
	shotPoint(ccp(0, 0)),
	weaponOriginPoint(ccp(0, 0))
{
	for(int i = 0 ; i < 5 ; i++)
		hearts[i] = NULL;
}

//----------------------------------------------------------------
BattleScene::~BattleScene()
{
	BattleScene::pSelf = NULL;
}

//----------------------------------------------------------------
void BattleScene::onEnter()
{
	CCLayer::onEnter();

	this->pBattleModel = BattleModel::create();
	this->pWeapon = Weapon::create();
	this->pWeapon->setBattleModel(this->pBattleModel);
}

//----------------------------------------------------------------
void BattleScene::onExit()
{
	CCLayer::onExit();
}

//----------------------------------------------------------------
bool BattleScene::init()
{
	if( !CCLayer::init() )
		return false;

	for(int i = 0 ; i < 5 ; i++)
	{
		this->hearts[i] = CCSprite::create("textures/scenes/battle/heart.png");
		this->hearts[i]->setAnchorPoint(ccp(0, 0));
		this->hearts[i]->setPosition(ccp(768 / 2 - 125 + i * 50 + 5, 970));
		this->addChild(this->hearts[i], 6);
	}

	CCSprite* bg = CCSprite::create("textures/scenes/battle/background.jpg");
	bg->setAnchorPoint(ccp(0, 0));
	bg->setPosition(ccp(0, 0));
	this->addChild(bg);
	//AMMO
	this->currentClipAmmoLabel = CCLabelBMFont::create("0", "fonts/days26black.fnt", 300.0f);
	this->currentClipAmmoLabel->setAnchorPoint(ccp(0, 0));
	this->currentClipAmmoLabel->setPosition(ccp(680, 950));
	this->addChild(this->currentClipAmmoLabel, 6);
	//
	this->currentFullAmmoLabel = CCLabelBMFont::create("0", "fonts/days26black.fnt", 500.0f);
	this->currentFullAmmoLabel->setAnchorPoint(ccp(0, 0));
	this->currentFullAmmoLabel->setPosition(ccp(630, 980));
	this->addChild(this->currentFullAmmoLabel, 6);	
	//
	CCSprite* pistol = CCSprite::create("textures/scenes/battle/pistol.png");
	CCSprite* pistolSelected = CCSprite::create("textures/scenes/battle/pistol_down.png");
	CCSprite* pistolDisabled = CCSprite::create("textures/scenes/battle/pistol.png");
	
	CCSprite* automatic = CCSprite::create("textures/scenes/battle/automatic.png");
	CCSprite* automaticSelected = CCSprite::create("textures/scenes/battle/automatic_down.png");
	CCSprite* automaticDisabled = CCSprite::create("textures/scenes/battle/automatic.png");
	
	CCSprite* rpg = CCSprite::create("textures/scenes/battle/rpg.png");
	CCSprite* rpgSelected = CCSprite::create("textures/scenes/battle/rpg_down.png");
	CCSprite* rpgDisabled = CCSprite::create("textures/scenes/battle/rpg.png");
	
	CCSprite* artillery = CCSprite::create("textures/scenes/battle/artilery.png");
	CCSprite* artillerySelected = CCSprite::create("textures/scenes/battle/artilery_down.png");
	CCSprite* artilleryDisabled = CCSprite::create("textures/scenes/battle/artilery.png");
	

	weaponSelection = CCMenu::create();
	weaponSelection->setPosition(ccp(0, 600));
	
	pistolMenuItem = CCMenuItemSprite::create(pistol, pistolSelected, this, menu_selector(BattleScene::weaponSelectionCallback1)); 
	pistolMenuItem->setAnchorPoint(ccp(0, 0));
	pistolMenuItem->setPosition(ccp(0, 0));
	weaponSelection->addChild(pistolMenuItem);

	automaticMenuItem = CCMenuItemSprite::create(automatic, automaticSelected,  this, menu_selector(BattleScene::weaponSelectionCallback2)); 
	automaticMenuItem->setAnchorPoint(ccp(0, 0));
	automaticMenuItem->setPosition(ccp(0, 100));
	weaponSelection->addChild(automaticMenuItem);

	rpgMenuItem = CCMenuItemSprite::create(rpg, rpgSelected,  this, menu_selector(BattleScene::weaponSelectionCallback3)); 
	rpgMenuItem->setAnchorPoint(ccp(0, 0));
	rpgMenuItem->setPosition(ccp(700, 0));
	weaponSelection->addChild(rpgMenuItem);

	artilleryMenuItem = CCMenuItemSprite::create(artillery, artillerySelected,  this, menu_selector(BattleScene::weaponSelectionCallback4)); 
	artilleryMenuItem->setAnchorPoint(ccp(0, 0));
	artilleryMenuItem->setPosition(ccp(700, 100));
	weaponSelection->addChild(artilleryMenuItem);

	CCMenu* menu = CCMenu::create();
	menu->setPosition(ccp(0, 970));
	this->addChild(menu, 5000);
	CCMenuItemImage* btnMainMenu = CCMenuItemImage::create("textures/scenes/shop/btnMainMenu.png", "textures/scenes/shop/btnMainMenu.png", this, menu_selector(BattleScene::onMainMenu));
	btnMainMenu->setPosition(ccp( 50, 0));
	menu->addChild(btnMainMenu, 20);

	this->addChild(weaponSelection, 5);

	this->scheduleUpdate();
	this->setTouchEnabled(true);

	return true;
}

//----------------------------------------------------------------
void BattleScene::update(float _dt)
{
	if(pBattleModel)
		pBattleModel->update(_dt);
	
	pWeapon->update(_dt);
	//
	ccColor4F colorLine = ccc4f(0.5, 0.5, 0.5, 0.3);
	ccColor4F colorLine1 = ccc4f(0.9, 0.0, 0.0, 0.1);
	
	pWeapon->onMoveShoting(shotPoint);

	//ammo indicators
	char currentClipAmmo[20];
	sprintf(currentClipAmmo, "%d", this->pWeapon->getSelectedWeaponChars()->m_curAmmo);
	this->currentClipAmmoLabel->setString(currentClipAmmo);

	char currentFullAmmo[20];
	if(this->pWeapon->getSelectedWeapon() == TW_PISTOL)
		sprintf(currentFullAmmo, "%d", Loader->getAmmoPistol());
	if(this->pWeapon->getSelectedWeapon() == TW_AUTOMATION)
		sprintf(currentFullAmmo, "%d", Loader->getAmmoAutomat());
	if(this->pWeapon->getSelectedWeapon() == TW_RPG)
		sprintf(currentFullAmmo, "%d", Loader->getAmmoRPG());
	if(this->pWeapon->getSelectedWeapon() == TW_ARTILLERY)
		sprintf(currentFullAmmo, "%d", Loader->getAmmoArtillery());
	this->currentFullAmmoLabel->setString(currentFullAmmo);

	//update hp bar
	for(int i = 0 ; i < 5 ; i++)
	{
		if(Memory->getHp() > i)
			this->hearts[i]->setVisible(true);
		else
			this->hearts[i]->setVisible(false);
	}

	//DEBUG
	if(pBattleModel)
	{
		pDebugScreen->removeAllChildren();
		std::vector<BattleObject*> battleObjects = pBattleModel->getBattleUnits();
		for(vector<BattleObject*>::iterator it = battleObjects.begin() ; it < battleObjects.end() ; it++)
		{
			pDebugScreen->drawCircle((*it)->getBattleUnit()->getPosition(), (*it)->getBattleUnit()->getRadius(), 50, colorLine);
		}
		pDebugScreen->drawCircle(weaponOriginPoint, pWeapon->getSelectedWeaponChars()->m_radius, 50, colorLine1);
	}
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::ccTouchesBegan(CCSet* _touches, CCEvent* _event)
{
	CCTouch* touch = NULL;
    
    CCSetIterator it;
    for (it = _touches->begin(); it != _touches->end(); ++it)
    {
        if (!(*it))
            break;
        touch = (CCTouch*)(*it);
		this->pWeapon->onShot(touch->getLocation());
		this->shotPoint = touch->getLocation();
	}
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::ccTouchesEnded(CCSet* _touches, CCEvent* _event)
{
	CCTouch* touch = NULL;
    
    CCSetIterator it;
    for (it = _touches->begin(); it != _touches->end(); ++it)
    {
        if (!(*it))
            break;
        touch = (CCTouch*)(*it);
		pWeapon->onEndShot();
	}
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::ccTouchesMoved(CCSet* _touches, CCEvent* _event)
{
	CCTouch* touch = NULL;
    
    CCSetIterator it;
    for (it = _touches->begin(); it != _touches->end(); ++it)
    {
        if (!(*it))
            break;
        touch = (CCTouch*)(*it);
		this->weaponOriginPoint = touch->getLocation();
		this->shotPoint = touch->getLocation();
	}
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::ccTouchesCancelled(CCSet* _touches, CCEvent* _event)
{
}

//----------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::weaponSelectionCallback1(CCObject* _pSender)
{
	this->pWeapon->setSelectedWeapon(TW_PISTOL);
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::weaponSelectionCallback2(CCObject* _pSender)
{
	this->pWeapon->setSelectedWeapon(TW_AUTOMATION);
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::weaponSelectionCallback3(CCObject* _pSender)
{
    this->pWeapon->setSelectedWeapon(TW_RPG);
}

//---------------------------------------------------------------------------------------------------------------------------------
void BattleScene::weaponSelectionCallback4(CCObject* _pSender)
{
    this->pWeapon->setSelectedWeapon(TW_ARTILLERY);
}

//----------------------------------------------------------------
void BattleScene::onMainMenu(CCObject* pSender)
{
	Loader->saveAllData();
	CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
}