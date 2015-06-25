#include "ReaderCity.h"
#include "tinyxml.h"
#include "Config.h"
#include "cocos2d.h"
#include "FileEncoder.h"

using namespace cocos2d;
using namespace std;

ReaderCity* ReaderCity::instance = NULL;

//------------------------------------------------------------------------------------------------
ReaderCity* ReaderCity::sharedInstance()
{
    if(!instance)
    {
        instance = new ReaderCity();
    }
    return instance;
}

//------------------------------------------------------------------------------------------------
void ReaderCity::destroy()
{
    if(instance)
    {
        delete instance;
    }
}

//------------------------------------------------------------------------------------------------
ReaderCity::ReaderCity()
{

}

//------------------------------------------------------------------------------------------------
ReaderCity::~ReaderCity()
{
	instance = NULL;
}

//------------------------------------------------------------------------------------------------
city* ReaderCity::loadCityByIdFromXML(int _id)
{
	FileEncoder::sharedInstance()->sharedInstance()->decode(GET_FULL_PATH(PATH_CITY_XML), GET_FULL_PATH(PATH_CITY_XML));
	//FileEncoder::sharedInstance()->sharedInstance()->encode(GET_FULL_PATH(PATH_PLAYER_XML), GET_FULL_PATH(PATH_PLAYER_XML));
	string str;
	city* location = NULL;

	TiXmlDocument worldFile(GET_FULL_PATH(PATH_CITY_XML));
	if(worldFile.LoadFile())
	{
		TiXmlElement* locationsElement = worldFile.FirstChildElement("locations");
		if(locationsElement)
		{
			TiXmlElement* locationElement = locationsElement->FirstChildElement("location");
			
			while(locationElement)
			{
				if(atoi(locationElement->Attribute("id")) == _id)
				{
					locationElement->QueryIntAttribute("id", &location->m_id);
					str = locationElement->Attribute("name");
					location->m_nameCity = new char[str.size() + 1];
					strcpy(location->m_nameCity, str.c_str());
					locationElement->QueryIntAttribute("price", &location->m_price);

					location->m_units.clear();

					TiXmlElement* unitElement = unitElement->FirstChildElement("unit");
					while(unitElement)
					{
						unit tUnit;
						str = unitElement->Attribute("name");
						tUnit.m_name = new char[str.size() + 1];
						
						if(tUnit.m_name == "simpleSoldier")
							tUnit.m_type = UT_SIMPLE_SOLDIER;
						else if(tUnit.m_name == "tank")
							tUnit.m_type == UT_TANK;

						unitElement->QueryFloatAttribute("genPercent", &tUnit.m_genPercent);
						unitElement->QueryFloatAttribute("hp", &tUnit.m_hp);
						unitElement->QueryFloatAttribute("radius", &tUnit.m_radius);
						unitElement->QueryFloatAttribute("money", &tUnit.m_money);					
					
						location->m_units.push_back(tUnit);

						unitElement->NextSiblingElement("unit");
					}
					return location;
				}
				//locationElement->NextSiblingElement("location");
			}
		}
	}
	//FileEncoder::sharedInstance()->encode(GET_FULL_PATH(PATH_PLAYER_XML), GET_FULL_PATH(PATH_PLAYER_XML));
	return NULL;
}
//------------------------------------------------------------------------------------------------