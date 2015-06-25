#include "DebugDrawScreen.h"
#include "DebugDraw.h"

using namespace cocos2d;

//---------------------------------------------------------------------------------------------------------------------------------
DebugDrawScreen* DebugDrawScreen::create()
{
    DebugDrawScreen* screen = new DebugDrawScreen();
    if(screen && screen->init())
    {
        screen->autorelease();
        return screen;
    }
    
    return NULL;
}

//---------------------------------------------------------------------------------------------------------------------------------
DebugDrawScreen::DebugDrawScreen()
{
}

//---------------------------------------------------------------------------------------------------------------------------------
DebugDrawScreen::~DebugDrawScreen()
{
}

//---------------------------------------------------------------------------------------------------------------------------------
bool DebugDrawScreen::init()
{
    //super init first
    if(!CCLayer::init())
        return false;

    
    //this->scheduleUpdate();
    this->setTouchEnabled(true);
    
    return true;
}

//---------------------------------------------------------------------------------------------------------------------------------
void DebugDrawScreen::onEnter()
{
    CCLayer::onEnter();
    
    CCLOG("DebugDrawScreen::onEnter");
}

//---------------------------------------------------------------------------------------------------------------------------------
void DebugDrawScreen::onExit()
{
    CCLayer::onExit();
    
    CCLOG("DebugDrawScreen::onExit");
}

//---------------------------------------------------------------------------------------------------------------------------------
void DebugDrawScreen::update(float _dt)
{
    
}

//---------------------------------------------------------------------------------------------------------------------------------
void DebugDrawScreen::ccTouchesBegan(CCSet* _touches, CCEvent* _event)
{
}

//---------------------------------------------------------------------------------------------------------------------------------
void DebugDrawScreen::ccTouchesEnded(CCSet* _touches, CCEvent* _event)
{
}

//---------------------------------------------------------------------------------------------------------------------------------
void DebugDrawScreen::ccTouchesMoved(CCSet* _touches, CCEvent* _event)
{
}

//---------------------------------------------------------------------------------------------------------------------------------
void DebugDrawScreen::ccTouchesCancelled(CCSet* _touches, CCEvent* _event)
{
}

//---------------------------------------------------------------------------------------------------------------------------------
void DebugDrawScreen::drawPoint(const cocos2d::CCPoint& _origin, float _size, const cocos2d::ccColor4F& _color)
{
    if(DEBUG_DRAW)
        this->addChild( DebugDrawPoint::create(_origin, _size, _color) );
}

//-----------------------------------------------------------------------------------------------------
void DebugDrawScreen::drawLine(const cocos2d::CCPoint& _origin, const cocos2d::CCPoint& _destination, const cocos2d::ccColor4F& _color)
{
    if(DEBUG_DRAW)
        this->addChild( DebugDrawLine::create(_origin, _destination, _color) );
}

//-----------------------------------------------------------------------------------------------------
void DebugDrawScreen::drawCircle(const cocos2d::CCPoint& _origin, float _radius, int _segs, const cocos2d::ccColor4F& _color)
{
    if(DEBUG_DRAW)
        this->addChild( DebugDrawCircle::create(_origin, _radius, 0, _segs, false, 1.0, 1.0, _color) );
}

//-----------------------------------------------------------------------------------------------------
void DebugDrawScreen::drawEllipse(const cocos2d::CCPoint& _origin, float _radiusH, float _radiusV, float _angle, int _segs, const cocos2d::ccColor4F& _color)
{
    if(DEBUG_DRAW)
        this->addChild( DebugDrawEllipse::create(_origin, _radiusH, _radiusV, _angle, _segs, false, _color) );
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------