#ifndef __ReaderPlayer__
#define __ReaderPlayer__

#include "Enums.h"

#define PATH_CITY_XML "xml/locations.xml"

//---------------------------------------------------------------------------------------------------------------------------------
class ReaderCity
{
public:
	static ReaderCity*			sharedInstance();
	void						destroy();
private:
	ReaderCity();
    ~ReaderCity();
	static ReaderCity*			instance;

public:
	city*						loadCityByIdFromXML(int _id);
};


//------------------------------------------------------------------------------------------------
#endif //__ReaderPlayer__