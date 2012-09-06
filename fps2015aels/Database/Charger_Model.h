#ifndef __CHARGER_MODEL_H__
#define __CHARGER_MODEL_H__

class Ammo_Model;

class Charger_Model
{
	public:
		Charger_Model(char** tab);
		~Charger_Model();
		int		Get_Id();
		void		Set_Id(int id);
		int		Get_Nb_Ammo();
		void		Set_Nb_Ammo(int nb_ammo);
		Ammo_Model*	Get_Ammo_Model();
		void		Set_Ammo_Model(Ammo_Model* ammo);

	private:
		int		__id;
		int		__nb_ammo_max;
		Ammo_Model*	__ammo_model;
};

#endif
