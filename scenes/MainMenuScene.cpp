#include "MainMenuScene.h"
#include "FabricBoxAmmunition.h"
#include "ShopScene.h"
#include "DataLoader.h"
#include "BattleScene.h"

using namespace cocos2d;

MainMenuScene* MainMenuScene::pSelf = NULL;

//---------------------------------------------------------------------------------------------------------------------------------
CCScene* MainMenuScene::scene()
{
    //'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    
    //'layer' is an autorelease object
    MainMenuScene::pSelf = MainMenuScene::create();
    scene->addChild( MainMenuScene::pSelf );

    return scene;
}

//---------------------------------------------------------------------------------------------------------------------------------
MainMenuScene::MainMenuScene():
m_isCreateBox(false),
m_maxCountBoxInStack(4),
m_distSlide(100.0f),
m_TimeMoveBox(0.5f)
{

}

//---------------------------------------------------------------------------------------------------------------------------------
MainMenuScene::~MainMenuScene()
{   
    MainMenuScene::pSelf = NULL;
}

//---------------------------------------------------------------------------------------------------------------------------------
bool MainMenuScene::init()
{
    //super init first
    if(!CCLayer::init())
        return false;

	m_vBoxAmmunitions.clear();
	
	initBackground();
	initInterface();
	this->initMenu();

    this->scheduleUpdate();
    this->setTouchEnabled(true);

    return true;
}

void MainMenuScene::initInterface()
{	
	CCSprite* pistol = CCSprite::create("textures/scenes/main/weapons/pistol_down.png");
	pistol->setPosition(ccp( SCREEN_WIDTH / 8, SCREEN_HEIGHT / 2));
	this->addChild(pistol);

	CCSprite* automatic = CCSprite::create("textures/scenes/main/weapons/automatic_down.png");
	automatic->setPosition(ccp( SCREEN_WIDTH / 8, SCREEN_HEIGHT / 1.5));
	this->addChild(automatic);

	CCSprite* rpg = CCSprite::create("textures/scenes/main/weapons/rpg_down.png");
	rpg->setPosition(ccp( SCREEN_WIDTH / 1.1, SCREEN_HEIGHT / 2));
	this->addChild(rpg);
		
	CCSprite* artilery = CCSprite::create("textures/scenes/main/weapons/artilery_down.png");
	artilery->setPosition(ccp( SCREEN_WIDTH / 1.1, SCREEN_HEIGHT / 1.5));
	this->addChild(artilery);

	char buf[50];

	sprintf(buf, "%d ", Loader->getAmmoPistol());
	m_countAmmoPistol = CCLabelTTF::create(buf, "Arial", 40);
	m_countAmmoPistol->setColor(ccWHITE);
	m_countAmmoPistol->setPosition(ccp( SCREEN_WIDTH / 4, SCREEN_HEIGHT / 1.7));	
	this->addChild(m_countAmmoPistol, 6546465);

	sprintf(buf, "%d ", Loader->getAmmoAutomat());
	m_countAmmoAutomatic = CCLabelTTF::create(buf, "Arial", 40);
	m_countAmmoAutomatic->setColor(ccWHITE);
	m_countAmmoAutomatic->setPosition(ccp( SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2.5));
	this->addChild(m_countAmmoAutomatic, 6898);

	sprintf(buf, "%d ", Loader->getAmmoRPG());
	m_countAmmoRpg = CCLabelTTF::create(buf, "Arial", 40);
	m_countAmmoRpg->setColor(ccWHITE);
	m_countAmmoRpg->setPosition(ccp( SCREEN_WIDTH / 1.2, SCREEN_HEIGHT / 1.7));
	this->addChild(m_countAmmoRpg, 5464);

	sprintf(buf, "%d ", Loader->getAmmoArtillery());
	m_countArtilery = CCLabelTTF::create(buf, "Arial", 40);
	m_countArtilery->setColor(ccWHITE);
	m_countArtilery->setPosition(ccp( SCREEN_WIDTH / 1.2, SCREEN_HEIGHT / 2.5));
	this->addChild(m_countArtilery, 45654);

	sprintf(buf, "%s ", Loader->getCurCity()->m_nameCity);
	CCLabelTTF* nameCity = CCLabelTTF::create(buf, "Arial", 40);
	nameCity->setColor(ccWHITE);
	nameCity->setPosition(ccp( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.1));
	this->addChild(nameCity, 45654);
}

void MainMenuScene::initBackground()
{
	// add background image	
    CCSprite* bg = CCSprite::create("textures/scenes/shop/bg/1.jpg");
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(ccp(0, SCREEN_HEIGHT / 2));
    this->addChild(bg);

	bg = CCSprite::create("textures/scenes/shop/bg/2.jpg");
	bg->setAnchorPoint(CCPointZero);
    bg->setPosition(ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    this->addChild(bg);
    //
    
	bg = CCSprite::create("textures/scenes/shop/bg/3.jpg");
	bg->setAnchorPoint(CCPointZero);
    bg->setPosition(ccp(0, 0));
    this->addChild(bg);
    //

	bg = CCSprite::create("textures/scenes/shop/bg/4.jpg");
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(ccp(SCREEN_WIDTH / 2, 0));
    this->addChild(bg);
    //
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::initMenu()
{
	CCMenuItemImage* btnShop = CCMenuItemImage::create("textures/scenes/shop/btnShop.png", "textures/scenes/shop/btnShop.png", this, menu_selector(MainMenuScene::onShop) );
	btnShop->setPosition(ccp( SCREEN_WIDTH / 10, SCREEN_HEIGHT / 1.1));

	CCMenuItemImage* btnBattle = CCMenuItemImage::create("textures/scenes/main/btnOnBattle.png", "textures/scenes/main/btnOnBattle.png", this, menu_selector(MainMenuScene::onBattle) );
	btnBattle->setPosition(ccp( SCREEN_WIDTH / 1.1, SCREEN_HEIGHT / 1.1));

	CCMenu* menu = CCMenu::create(btnShop, btnBattle, NULL);	
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::onEnter()
{
    CCLayer::onEnter();
    CCLOG("MainMenuScene::onEnter");
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::onShop(CCObject* pSender)
{
	Loader->saveAllData();

	CCDirector::sharedDirector()->replaceScene(ShopScene::scene());
}
void MainMenuScene::onBattle(CCObject* pSender)
{
	Loader->saveAllData();
	CCDirector::sharedDirector()->replaceScene(BattleScene::scene());
}
//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::createBox()
{
	if(m_vBoxAmmunitions.size() < m_maxCountBoxInStack)
	{
		IBoxAmmunition* box = FabricBoxAmmunition::createRandomBox();
		box->setPosition(ccp(SCREEN_WIDTH / 2, 0));
		this->addChild(box);
		
		cocos2d::CCFiniteTimeAction* curActionMove = CCMoveTo::create(m_TimeMoveBox, ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		curActionMove->startWithTarget(box);
		
		CCCallFuncND* afterMove = CCCallFuncND::create(this, callfuncND_selector(MainMenuScene::endMoveBox), this);
		CCSequence* sequence = CCSequence::create(curActionMove, afterMove, NULL);
		
		box->runAction(sequence);

		m_vBoxAmmunitions.push_back(box);
	}
}
//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::endMoveBox(CCNode* sender, void* data)
{
	/*
	IBoxAmmunition *box = static_cast<IBoxAmmunition*>(data);
	MainMenuScene *pScene = dynamic_cast<MainMenuScene*>(sender);
	*/
	IBoxAmmunition *box = dynamic_cast<IBoxAmmunition*>(sender);
	MainMenuScene *pScene = static_cast<MainMenuScene*>(data);
	//if(pScene->m_vBoxAmmunitions.size() == 1)
	//{
		//box->showIconAmmo();
		box->increaseAmmo();
	//}

	vector<IBoxAmmunition*>::iterator iterRemove = NULL;

	for (vector<IBoxAmmunition*>::iterator i = m_vBoxAmmunitions.begin(); i < m_vBoxAmmunitions.end(); i++)
	{
		if((*i) == box)
		{
			iterRemove = i;
			break;
		}
	}

	CCFadeTo* fadeToBox = CCFadeTo::create(1, 0);
	box->runAction(fadeToBox);

	CCFadeOut* fadeOut = CCFadeOut::create( 1.0f );
	box->runAction(fadeOut);

	if(iterRemove)
		pScene->m_vBoxAmmunitions.erase(iterRemove);
}
//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::onExit()
{
    CCLayer::onExit();
    CCLOG("MainMenuScene::onExit");
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::update(float _dt)
{
	char buf[50];

	DataLoader* pLoader = Loader;

	sprintf(buf, "%d ", pLoader->getAmmoPistol());
	m_countAmmoPistol->setString(buf);

	sprintf(buf, "%d ", pLoader->getAmmoAutomat());
	m_countAmmoAutomatic->setString(buf);

	sprintf(buf, "%d ", pLoader->getAmmoRPG());
	m_countAmmoRpg->setString(buf);

	sprintf(buf, "%d ", pLoader->getAmmoArtillery());
	m_countArtilery->setString(buf);
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::ccTouchesBegan(CCSet* _touches, CCEvent* _event)
{
	CCTouch* touch = NULL;
	touch = dynamic_cast<CCTouch*>(_touches->anyObject());
	if(touch)
		m_ptTouch = touch->getLocation();
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::ccTouchesEnded(CCSet* _touches, CCEvent* _event)
{
	m_isCreateBox = false;
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::ccTouchesMoved(CCSet* _touches, CCEvent* _event)
{
	CCTouch* touch = NULL;
	touch = dynamic_cast<CCTouch*>(_touches->anyObject());
	if(touch && m_isCreateBox == false)
	{
		if(m_distSlide <= ccpDistance(m_ptTouch, touch->getLocation()))
		{
			m_isCreateBox = true;
			createBox();
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------
void MainMenuScene::ccTouchesCancelled(CCSet* _touches, CCEvent* _event)
{
}