#ifndef __WEAPON_MODEL_H__
#define __WEAPON_MODEL_H__

class	Fire_Model;
class	Charger_Model;
class	Weapon_Model
{
	public:
		Weapon_Model(char** data);
		~Weapon_Model();
		int		Get_Id();
		void		Set_Id(int);
//		void		Set_Object(Object*);
//		Object*		Get_Object();
		Fire_Model*	Get_Fire_Primary();
		void		Set_Fire_Primary(Fire_Model*);
		void		Set_Fire_Primary_With_Id(int id);
		Fire_Model*	Get_Fire_Secondary();
		void		Set_Fire_Secondary(Fire_Model*);
		void		Set_Fire_Secondary_With_Id(int id);
		int		Get_Nb_Charger1();
		void		Set_Nb_Chargeur1(int);
		int		Get_Nb_Charger2();
		void		Set_Nb_Charger2(int);
		Charger_Model*	Get_Charger1();
		Charger_Model*	Get_Charger2();
	private:
		int		__id;
		int		__nb_charger1;
		int		__nb_charger2;
		bool		__auto;
//		Object*		__object;
		Fire_Model*	__primary_fire;
		Fire_Model*	__secondary_fire;
		Charger_Model*	__charger1;
		Charger_Model*	__charger2;
};

#endif
