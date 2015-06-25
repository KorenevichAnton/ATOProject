#ifndef __MAIN_MENU_SCENE__
#define __MAIN_MENU_SCENE__

#include "IScene.h"
#include "IBoxAmmunition.h"
#include "ReaderPlayer.h"

using namespace std;

//-----------------------------------------------------------------------------------------------------------------------------
class MainMenuScene: public IScene
{
public:
    static MainMenuScene*       pSelf;   
    static cocos2d::CCScene*    scene();
	void						createBox();
private:
	void						onShop(CCObject* pSender);
	void						onBattle(CCObject* pSender);

	vector<IBoxAmmunition*>		m_vBoxAmmunitions;

	//move box ammo
	CCPoint						m_ptTouch;
	float						m_distSlide;
	bool						m_isCreateBox;
	int							m_maxCountBoxInStack;
	float						m_TimeMoveBox;
	void						endMoveBox(CCNode* sender, void* data);
	//

	void			initBackground();
	void			initInterface();

    bool            init();
    void            initMenu();
    
    void            update(float _dt);

    void            onEnter();
    void            onExit();
    
    CREATE_FUNC(MainMenuScene);
    
    MainMenuScene();
    ~MainMenuScene();
    
	CCLabelTTF*		m_countAmmoPistol;
    CCLabelTTF*		m_countAmmoAutomatic;
	CCLabelTTF*		m_countAmmoRpg;
	CCLabelTTF*		m_countArtilery;
	
    //touch events
    void            ccTouchesBegan(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void            ccTouchesEnded(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void            ccTouchesMoved(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void            ccTouchesCancelled(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__MAIN_MENU_SCENE__