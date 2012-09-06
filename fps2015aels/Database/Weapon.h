#ifndef __WEAPON_H__
#define __WEAPON_H__

class Weapon_Model;
class Charger;
class Weapon
{
	public:
		Weapon(Weapon_Model* weapon);
		~Weapon();
		Weapon_Model*	Get_Weapon_Model();
		int		Get_Id();
		void		Fire(bool fire);
		Charger*	Get_Charger1();
		Charger*	Get_Charger2();
	private:
		Weapon_Model*	__weapon_model;
		int		__id;
		Charger*	__charger1;
		Charger*	__charger2;
		bool		__same_ammo;
};

#endif
