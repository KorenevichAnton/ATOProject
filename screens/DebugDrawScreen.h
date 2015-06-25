#ifndef __DEBUG_DRAW_SCREEN__
#define __DEBUG_DRAW_SCREEN__

#include "IScreen.h"
#include "cocos2d.h"

//---------------------------------------------------------------------------------------------------------------------------------
class DebugDrawScreen: public IScreen
{
public:
    static DebugDrawScreen* create();
   
    void                    drawPoint(const cocos2d::CCPoint& _origin, float _size, const cocos2d::ccColor4F& _color);
	void                    drawLine(const cocos2d::CCPoint& _origin, const cocos2d::CCPoint& _destination, const cocos2d::ccColor4F& _color);
	void                    drawCircle(const cocos2d::CCPoint& _origin, float _radius, int _segs, const cocos2d::ccColor4F& _color);
	void                    drawEllipse(const cocos2d::CCPoint& _origin, float _radiusH, float _radiusV, float _angle, int _segs, const cocos2d::ccColor4F& _color);
    
private:
    
    bool                    init();

    void                    update(float _dt);

    void                    onEnter();
    void                    onExit();

    DebugDrawScreen();
    ~DebugDrawScreen();
    
    
    //touch events
    void                    ccTouchesBegan(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void                    ccTouchesEnded(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void                    ccTouchesMoved(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void                    ccTouchesCancelled(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__DEBUG_DRAW_SCREEN__