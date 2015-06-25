#ifndef __ReaderWeapons__
#define __ReaderWeapons__

#include "cocos2d.h"
#include "Enums.h"

#define PATH_WEAPON_PISTOL "xml/weapons/weaponPistol.xml"
#define PATH_WEAPON_AUTOMATION "xml/weapons/weaponAutomation.xml"
#define PATH_WEAPON_RPG "xml/weapons/weaponRPG.xml"
#define PATH_WEAPON_ARTILLERY "xml/weapons/weaponArtillery.xml"

//---------------------------------------------------------------------------------------------------------------------------------
class ReaderWeapons
{
public:
	static ReaderWeapons*		sharedInstance();
	void						destroy();
private:
	ReaderWeapons();
    ~ReaderWeapons();
	static ReaderWeapons*		instance;

public:
	CharacteristicsWeapons*					 getWeaponByIdFromXML(char* _path, int _id);
	std::vector<CharacteristicsWeapons>		 getWeaponsFromXML(char* _path);
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__CTimer__