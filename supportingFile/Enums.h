#ifndef __ALL_ENUMS_H__
#define __ALL_ENUMS_H__

#include <vector>

enum type_weapon{
	TW_PISTOL = 0,
	TW_AUTOMATION = 1,
	TW_RPG = 2,
	TW_ARTILLERY = 3
};

enum BattleUnitType
{
	UT_NONE = -1,
	UT_SIMPLE_SOLDIER = 0,
	UT_TANK
};

struct CharacteristicsWeapons
{
	int		m_id;
	int		m_price;
	char*	m_name;
	int		m_damage;
	int		m_speed;
	int		m_countAmmo;
	int		m_radius;
	int		m_curAmmo;
	float	m_reloadTimer;
	bool	m_reloadingState;
};

struct CharacteristicPlayer
{
	int				m_money;
	int				m_idCity;

	int				m_idPistol;
	int				m_idAutomaton;
	int				m_idRpg;
	int				m_idArtillery;

	int				m_ammoPistol;
	int				m_ammoAutomaton;
	int				m_ammoRpg;
	int				m_ammoArtillery;
};

struct unit
{
	char*			m_name;
	BattleUnitType	m_type;
	float			m_hp;
	float			m_radius;
	float			m_money;
	float			m_genPercent;
};

struct city
{
	int						m_id;
	char*					m_nameCity;
	int						m_price;
	std::vector<unit>		m_units;							
};


#endif  // __ALL_ENUMS_H__