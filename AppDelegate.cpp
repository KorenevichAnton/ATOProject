#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "MainMenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);

    // turn on display FPS
    pDirector->setDisplayStats(false);

	CCSize designResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

	float scaleFactorHeight = pDirector->getWinSize().height / designResolutionSize.height;
    float scaleFactorWidth = pDirector->getWinSize().width / designResolutionSize.width;
    float scaleFactor = (scaleFactorHeight < scaleFactorWidth)?scaleFactorHeight : scaleFactorWidth;
    CCDirector::sharedDirector()->setContentScaleFactor(scaleFactor);
	
	// set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(FPS);

	CCScene *pScene = MainMenuScene::scene();
	CCDirector::sharedDirector()->runWithScene(pScene);

	//CCDirector::sharedDirector()->setContentScaleFactor(1);

	srand(time(NULL));

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
}
