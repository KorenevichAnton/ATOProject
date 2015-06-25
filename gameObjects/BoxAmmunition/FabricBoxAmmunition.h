#ifndef __FabricBoxAmmunition__
#define __FabricBoxAmmunition__

#include "IBoxAmmunition.h"
#include "Enums.h"

//---------------------------------------------------------------------------------------------------------------------------------
class FabricBoxAmmunition
{
public:
	static IBoxAmmunition* create(type_weapon _type);
	static IBoxAmmunition* createRandomBox();
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__IBoxAmmunition__