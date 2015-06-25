#include "ReaderPlayer.h"
#include "tinyxml.h"
#include "Config.h"
#include "cocos2d.h"
#include "FileEncoder.h"

using namespace cocos2d;
using namespace std;

ReaderPlayer* ReaderPlayer::instance = NULL;

ReaderPlayer* ReaderPlayer::sharedInstance()
{
    if(!instance)
    {
        instance = new ReaderPlayer();
    }
    return instance;
}

void ReaderPlayer::destroy()
{
    if(instance)
    {
        delete instance;
    }
}


//---------------------------------------------------------------------------------------------------------------------------------
ReaderPlayer::ReaderPlayer()
{

}

//---------------------------------------------------------------------------------------------------------------------------------
ReaderPlayer::~ReaderPlayer()
{
	instance = NULL;
}

//---------------------------------------------------------------------------------------------------------------------------------
CharacteristicPlayer ReaderPlayer::loadPlayerFromXML()
{
	FileEncoder::sharedInstance()->sharedInstance()->decode(GET_FULL_PATH(PATH_PLAYER_XML), GET_FULL_PATH(PATH_PLAYER_XML));
	//FileEncoder::sharedInstance()->sharedInstance()->encode(GET_FULL_PATH(PATH_PLAYER_XML), GET_FULL_PATH(PATH_PLAYER_XML));
	CharacteristicPlayer player;
	TiXmlDocument worldFile(GET_FULL_PATH(PATH_PLAYER_XML));

	if(worldFile.LoadFile())
	{
		TiXmlElement* playerElement = worldFile.FirstChildElement("player");
		if(playerElement)
		{
			player.m_idArtillery = 0;
			player.m_idAutomaton = 0;
			player.m_idCity = 0;
			player.m_idPistol = 0;
			player.m_idRpg = 0;
			player.m_money = 0;
			
			TiXmlElement* moneyElement = playerElement->FirstChildElement("money");
			TiXmlElement* cityElement = playerElement->FirstChildElement("city");
			TiXmlElement* pistolElement = playerElement->FirstChildElement("pistol");
			TiXmlElement* automatonElement = playerElement->FirstChildElement("automaton");
			TiXmlElement* rpgElement = playerElement->FirstChildElement("rpg");
			TiXmlElement* artileryElement = playerElement->FirstChildElement("artilery");

			moneyElement->QueryIntAttribute("count", &player.m_money);
			cityElement->QueryIntAttribute("id", &player.m_idCity);
			pistolElement->QueryIntAttribute("id", &player.m_idPistol);
			automatonElement->QueryIntAttribute("id", &player.m_idAutomaton);
			rpgElement->QueryIntAttribute("id", &player.m_idRpg);
			artileryElement->QueryIntAttribute("id", &player.m_idArtillery);

			pistolElement->QueryIntAttribute("countAmmo", &player.m_ammoPistol);
			automatonElement->QueryIntAttribute("countAmmo", &player.m_ammoAutomaton);
			rpgElement->QueryIntAttribute("countAmmo", &player.m_ammoRpg);
			artileryElement->QueryIntAttribute("countAmmo", &player.m_ammoArtillery);
		}
	}
	//FileEncoder::sharedInstance()->encode(GET_FULL_PATH(PATH_PLAYER_XML), GET_FULL_PATH(PATH_PLAYER_XML));
	return player;
}

//---------------------------------------------------------------------------------------------------------------------------------
void ReaderPlayer::savePlayerToXML(CharacteristicPlayer _player)
{
	FileEncoder::sharedInstance()->decode(GET_FULL_PATH(PATH_PLAYER_XML), GET_FULL_PATH(PATH_PLAYER_XML));

	TiXmlDocument worldFile(GET_FULL_PATH(PATH_PLAYER_XML));

	if(worldFile.LoadFile())
	{
		TiXmlElement* playerElement = worldFile.FirstChildElement("player");
		if(playerElement)
		{		
			TiXmlElement* moneyElement = playerElement->FirstChildElement("money");
			TiXmlElement* cityElement = playerElement->FirstChildElement("city");
			TiXmlElement* pistolElement = playerElement->FirstChildElement("pistol");
			TiXmlElement* automatonElement = playerElement->FirstChildElement("automaton");
			TiXmlElement* rpgElement = playerElement->FirstChildElement("rpg");
			TiXmlElement* artileryElement = playerElement->FirstChildElement("artilery");

			
			moneyElement->SetAttribute("count", _player.m_money);
			cityElement->SetAttribute("id", _player.m_idCity);
			pistolElement->SetAttribute("id", _player.m_idPistol);
			automatonElement->SetAttribute("id", _player.m_idAutomaton);
			rpgElement->SetAttribute("id", _player.m_idRpg);
			artileryElement->SetAttribute("id", _player.m_idArtillery);

			pistolElement->SetAttribute("countAmmo", _player.m_ammoPistol);
			automatonElement->SetAttribute("countAmmo", _player.m_ammoAutomaton);
			rpgElement->SetAttribute("countAmmo", _player.m_ammoRpg);
			artileryElement->SetAttribute("countAmmo", _player.m_ammoArtillery);
		}
		worldFile.SaveFile();
	}

	FileEncoder::sharedInstance()->encode(GET_FULL_PATH(PATH_PLAYER_XML), GET_FULL_PATH(PATH_PLAYER_XML));
}