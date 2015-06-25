#ifndef __IBoxAmmunition__
#define __IBoxAmmunition__

#include "cocos2d.h"
#include "MemoryProfiler.h"
#include "Enums.h"

using namespace cocos2d;

//---------------------------------------------------------------------------------------------------------------------------------
class IBoxAmmunition : /*public CCLayer,*/ public CCNodeRGBA
{
public:
	virtual void		increaseAmmo() = 0;
protected:
	CCSprite*			m_box;
	CCSprite*			m_IconAmmo;
	CCSprite*			m_BackgroundIconAmmo;
	CCLabelBMFont*		m_lCountAmmo;	
	int					m_CountAmmo;
	type_weapon			m_type;
public:
	IBoxAmmunition() : 
	m_box(NULL),
	m_BackgroundIconAmmo(NULL),
	m_IconAmmo(NULL),
	m_lCountAmmo(NULL)
	{}

	virtual void		showIconAmmo() 
	{ 
		this->m_box->setVisible(false);
		this->m_BackgroundIconAmmo->setVisible(true);
		this->m_IconAmmo->setVisible(true);
		this->m_lCountAmmo->setVisible(true);
	}	

	virtual void		setOpacity(GLubyte _opacity) 
	{ 
		this->m_box->setOpacity(_opacity);
		this->m_BackgroundIconAmmo->setOpacity(_opacity);
		this->m_IconAmmo->setOpacity(_opacity);
		this->m_lCountAmmo->setOpacity(_opacity);
	}

	virtual void		showBoxAmmo() 
	{ 
		this->m_box->setVisible(true);
		this->m_BackgroundIconAmmo->setVisible(false);
		this->m_IconAmmo->setVisible(false);
		this->m_lCountAmmo->setVisible(false);
	}

	virtual bool			   			init() = 0;
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__IBoxAmmunition__