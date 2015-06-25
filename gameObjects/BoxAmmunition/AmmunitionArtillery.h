#ifndef __AmmunitionArtillery__
#define __AmmunitionArtillery__

#include "IBoxAmmunition.h"

//---------------------------------------------------------------------------------------------------------------------------------
class AmmunitionArtillery : public IBoxAmmunition
{
public:
	void		increaseAmmo();
public:
	bool		init();
	static AmmunitionArtillery*				create(int _countAmmo);
private:
    AmmunitionArtillery();
    ~AmmunitionArtillery();
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__AmmunitionArtillery__