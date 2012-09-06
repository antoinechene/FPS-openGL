#ifndef __DATABASE_H__
#define __DATABASE_H__
#include "../uilibgp2015/OGL/ID_glibrary.h"
#include <vector>

class	Weapon_Model;
class	Ammo_Model;
class	Fire_Model;
class	Charger_Model;
class	Sound_Model;
class	Database : public ID::Singleton<Database>
{
	friend class	ID::Singleton<Database>;
	public:
				Database();
				~Database();
		int		Init();
		int		Init_Weapon_Db();
		int		Init_Ammo_Db();
		int		Init_Fire_Db();
		int		Init_Charger_Db();
		int		Init_Sound_Db();
		Weapon_Model*	Get_Weapon_Model(int id);
		Ammo_Model*	Get_Ammo_Model(int id);
		Fire_Model*	Get_Fire_Model(int id);
		Charger_Model*	Get_Charger_Model(int id);
		Sound_Model*	Get_Sound_Model(int id);
	private:
		std::vector<Weapon_Model*>	__weapon_db;
		std::vector<Ammo_Model*>	__ammo_db;
		std::vector<Fire_Model*>	__fire_db;
	public:
		std::vector<Charger_Model*>	__charger_db;
		std::vector<Sound_Model*>	__sound_db;
};

#endif
