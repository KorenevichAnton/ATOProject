#ifndef __SHOP_SCENE__
#define __SHOP_SCENE__

#include "IScene.h"
#include "IBoxAmmunition.h"
#include "YesNoScreen.h"
#include "NotEnoughScreen.h"

using namespace std;

//-----------------------------------------------------------------------------------------------------------------------------
class ShopScene: public IScene
{
public:
    static ShopScene*			pSelf;   
    static cocos2d::CCScene*    scene();
private:
	CREATE_FUNC(ShopScene);
    ShopScene();
    ~ShopScene();
    
	bool            init();
  
    void            update(float _dt);
    void            onEnter();
    void            onExit();

	//touch events
    void            ccTouchesBegan(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void            ccTouchesEnded(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void            ccTouchesMoved(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);
    void            ccTouchesCancelled(cocos2d::CCSet* _touches, cocos2d::CCEvent* _event);

public:
	void				updateLabeUpgradeCity();
	void				updateLabeUpgradePistol();
	void				updateLabeUpgradeAutomaton();
	void				updateLabeUpgradeRpg();
	void				updateLabeUpgradeArtilery();
	NotEnoughScreen*	getNotEnoughScreen() { return m_notEnoughScreen; }
	CCMenu*				getMenuBtn() { return m_menuBtn; }
	
private:
	void			onUpgradePistol(CCObject* pSender);
	void			onUpgradeAutomatic(CCObject* pSender);
	void			onUpgradeRpg(CCObject* pSender);
	void			onUpgradeArtilery(CCObject* pSender);

	void			onAddMoney(CCObject* pSender);
	void			onAddAmmoPistol(CCObject* pSender);
	void			onAddAmmoAutomatic(CCObject* pSender);
	void			onAddAmmoRpg(CCObject* pSender);
	void			onAddAmmoArtilery(CCObject* pSender);

	void			initBackground();
	void			initInterface();
	void            initMenu();
	void			onMainMenu(CCObject* pSender);

	NotEnoughScreen*	m_notEnoughScreen;
	YesNoScreen*		m_yesNoPurchase;
    
	CCLabelBMFont*		m_countAmmoPistol;
    CCLabelBMFont*		m_countAmmoAutomatic;
	CCLabelBMFont*		m_countAmmoRpg;
	CCLabelBMFont*		m_countAmmoArtilery;

	CCLabelBMFont*		m_powerPistol;
    CCLabelBMFont*		m_powerAutomatic;
	CCLabelBMFont*		m_powerRpg;
	CCLabelBMFont*		m_powerArtilery;

	CCLabelBMFont*		m_speedPistol;
    CCLabelBMFont*		m_speedAutomatic;
	CCLabelBMFont*		m_speedRpg;
	CCLabelBMFont*		m_speedArtilery;

	CCLabelBMFont*		m_countAmmoCagePistol;
    CCLabelBMFont*		m_countAmmoCageAutomatic;
	CCLabelBMFont*		m_countAmmoCageRpg;
	CCLabelBMFont*		m_countAmmoCageArtilery;

	CCLabelBMFont*		m_radiusPistol;
    CCLabelBMFont*		m_radiusAutomatic;
	CCLabelBMFont*		m_radiusRpg;
	CCLabelBMFont*		m_radiusArtilery;
	
	CCLabelTTF*			m_priceUpgradeCity;
	CCLabelBMFont*		m_priceUpgradePistol;
    CCLabelBMFont*		m_priceUpgradeAutomatic;
	CCLabelBMFont*		m_priceUpgradeRpg;
	CCLabelBMFont*		m_priceUpgradeArtilery;

	CCMenu*				m_menuBtn;
	CCMenuItemImage*	upgradePistol;
	CCMenuItemImage*	upgradeAutomatic;
	CCMenuItemImage*	upgradeRpg;
	CCMenuItemImage*	upgradeArtilery;
	CCMenuItemImage*	m_upgradeCity;

	CCLabelTTF*			m_nameNextCity;
	CCLabelTTF*			m_myMoney;
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__MAIN_MENU_SCENE__