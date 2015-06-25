#include "ReaderWeapons.h"
#include "tinyxml.h"
#include "Config.h"

using namespace cocos2d;
using namespace std;

ReaderWeapons* ReaderWeapons::instance = NULL;

ReaderWeapons* ReaderWeapons::sharedInstance()
{
    if(!instance)
    {
        instance = new ReaderWeapons();
    }
    return instance;
}

void ReaderWeapons::destroy()
{
    if(instance)
    {
        delete instance;
    }
}


//---------------------------------------------------------------------------------------------------------------------------------
ReaderWeapons::ReaderWeapons()
{

}

//---------------------------------------------------------------------------------------------------------------------------------
ReaderWeapons::~ReaderWeapons()
{
	instance = NULL;
}

//---------------------------------------------------------------------------------------------------------------------------------
CharacteristicsWeapons* ReaderWeapons::getWeaponByIdFromXML(char* _path, int _id)
{
	CharacteristicsWeapons* weapon = NULL;
	string tStr;
	TiXmlDocument worldFile(GET_FULL_PATH(_path));
	if(worldFile.LoadFile())
	{
		TiXmlElement* rootElement = worldFile.FirstChildElement("weapons");
		if(rootElement)
		{
			//init physical world matrix
			TiXmlElement* weaponElement = rootElement->FirstChildElement("weapon");

			while(weaponElement)
			{
				if(atoi(weaponElement->Attribute("id")) == _id)
				{
					weapon = new CharacteristicsWeapons();
					weapon->m_id = 0;
					weapon->m_countAmmo = 0;
					weapon->m_damage = 0;
					weapon->m_name = NULL;
					weapon->m_price = 0;
					weapon->m_radius = 0;
					weapon->m_speed = 0;

					weapon->m_id = _id;
					weaponElement->QueryIntAttribute("price", &weapon->m_price);

					tStr = weaponElement->Attribute("name");
					weapon->m_name = new char[tStr.size() + 1];
					strcpy(weapon->m_name, tStr.c_str());
					weaponElement->QueryIntAttribute("damage", &weapon->m_damage);
					weaponElement->QueryIntAttribute("speed", &weapon->m_speed);
					weaponElement->QueryIntAttribute("countAmmo", &weapon->m_countAmmo);
					weaponElement->QueryIntAttribute("radius", &weapon->m_radius);
					break;
				}
				weaponElement = weaponElement->NextSiblingElement("weapon");
			}
		}
	}
	return weapon;
}
//---------------------------------------------------------------------------------------------------------------------------------
std::vector<CharacteristicsWeapons>	ReaderWeapons::getWeaponsFromXML(char* _path)
{
	vector<CharacteristicsWeapons> vWeapons;
	vWeapons.clear();

	string tStr;
	CharacteristicsWeapons tWeapon;
	
	TiXmlDocument worldFile(GET_FULL_PATH(_path));
	if(worldFile.LoadFile())
	{
		TiXmlElement* rootElement = worldFile.FirstChildElement("weapons");
		if(rootElement)
		{
			//init physical world matrix
			TiXmlElement* weaponElement = rootElement->FirstChildElement("weapon");

			while(weaponElement)
			{
				weaponElement->QueryIntAttribute("price", &tWeapon.m_id);
				weaponElement->QueryIntAttribute("price", &tWeapon.m_price);
				tStr = weaponElement->Attribute("name");
				tWeapon.m_name = new char[tStr.size() + 1];
				strcpy(tWeapon.m_name, tStr.c_str());
				weaponElement->QueryIntAttribute("damage", &tWeapon.m_damage);
				weaponElement->QueryIntAttribute("speed", &tWeapon.m_speed);
				weaponElement->QueryIntAttribute("countAmmo", &tWeapon.m_countAmmo);
				weaponElement->QueryIntAttribute("radius", &tWeapon.m_radius);

				vWeapons.push_back(tWeapon);

				weaponElement = weaponElement->NextSiblingElement("weapon");
			}
		}
	}
	return vWeapons;
}
//---------------------------------------------------------------------------------------------------------------------------------