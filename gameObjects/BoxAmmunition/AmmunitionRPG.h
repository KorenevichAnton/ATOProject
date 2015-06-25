#ifndef __AmmunitionRPG__
#define __AmmunitionRPG__

#include "IBoxAmmunition.h"

//---------------------------------------------------------------------------------------------------------------------------------
class AmmunitionRPG : public IBoxAmmunition
{
public:
	void		increaseAmmo();
public:
	bool		init();
	static AmmunitionRPG*				create(int _countAmmo);
private:
    AmmunitionRPG();
    ~AmmunitionRPG();
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__AmmunitionRPG__