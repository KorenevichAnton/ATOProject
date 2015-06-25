#ifndef __ReaderPlayer__
#define __ReaderPlayer__

#include "Enums.h"

#define PATH_PLAYER_XML "xml/player.xml"

//---------------------------------------------------------------------------------------------------------------------------------
class ReaderPlayer
{
public:
	static ReaderPlayer*		sharedInstance();
	void						destroy();
private:
	ReaderPlayer();
    ~ReaderPlayer();
	static ReaderPlayer*		instance;

public:
	CharacteristicPlayer		loadPlayerFromXML();
	void						savePlayerToXML(CharacteristicPlayer _player);
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__CTimer__