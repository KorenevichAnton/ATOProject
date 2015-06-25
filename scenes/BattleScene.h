#ifndef __BattleScene__
#define __BattleScene__

#include "cocos2d.h"
#include "BattleModel.h"
#include "Weapon.h"
#include "DebugDrawScreen.h"

class BattleScene : public cocos2d::CCLayer
{
public:
	static BattleScene*				pSelf;

	static cocos2d::CCScene*		scene();

	CREATE_FUNC( BattleScene );

private:
	bool							init();

	void							onEnter();
	void							onExit();

	BattleScene();
	~BattleScene();
	
	//touch events
    void                ccTouchesBegan(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void                ccTouchesEnded(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void                ccTouchesMoved(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void                ccTouchesCancelled(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);

public:
	void							update(float _dt);
	//main weapon selection callbacks
    void				weaponSelectionCallback1(CCObject* _pSender);
    void				weaponSelectionCallback2(CCObject* _pSender);
    void				weaponSelectionCallback3(CCObject* _pSender);
    void				weaponSelectionCallback4(CCObject* _pSender);
	//
	CCLayer*			getBattleLayer() { return battleLayer; };
	BattleModel*		getBattleModel() { return pBattleModel; };


private:
	void				onMainMenu(CCObject* pSender);

	BattleModel*		pBattleModel;
	CCLayer*			battleLayer;
	//
	Weapon*				pWeapon;
	cocos2d::CCPoint	shotPoint;
	//
	cocos2d::CCLabelBMFont* currentClipAmmoLabel;
	cocos2d::CCLabelBMFont* currentFullAmmoLabel;
	//DEBUG
	DebugDrawScreen*				pDebugScreen;
	cocos2d::CCPoint				weaponOriginPoint;
	//
	cocos2d::CCMenu*				weaponSelection;
	cocos2d::CCMenuItemSprite*		pistolMenuItem;
	cocos2d::CCMenuItemSprite*		automaticMenuItem;
	cocos2d::CCMenuItemSprite*		rpgMenuItem;
	cocos2d::CCMenuItemSprite*		artilleryMenuItem;
	//TEMP HP
	cocos2d::CCSprite*				hearts[5];
};

#endif //__BattleModel__