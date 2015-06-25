#ifndef __AmmunitionAutomation__
#define __AmmunitionAutomation__

#include "IBoxAmmunition.h"

//---------------------------------------------------------------------------------------------------------------------------------
class AmmunitionAutomation : public IBoxAmmunition
{
public:
	void		increaseAmmo();
public:
	bool		init();
	static AmmunitionAutomation*				create(int _countAmmo);
private:
    AmmunitionAutomation();
    ~AmmunitionAutomation();
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__AmmunitionAutomation__