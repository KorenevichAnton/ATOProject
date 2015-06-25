#ifndef __AmmunitionPistol__
#define __AmmunitionPistol__

#include "IBoxAmmunition.h"

//---------------------------------------------------------------------------------------------------------------------------------
class AmmunitionPistol : public IBoxAmmunition
{
public:
	void							increaseAmmo();
public:
	bool							init();
	static AmmunitionPistol*		create(int _countAmmo);
private:
    AmmunitionPistol();
    ~AmmunitionPistol();
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__AmmunitionPistol__