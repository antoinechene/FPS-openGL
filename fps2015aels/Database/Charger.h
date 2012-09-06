#ifndef __CHARGER_H__
#define __CHARGER_H__

class Ammo_Model;
class Charger_Model;

class Charger
{
	public:
		Charger(Charger_Model* model);
		~Charger();
		int		Get_Id();
		void		Set_Id(int id);
		int		Get_Nb_Ammo();
		void		Set_Nb_Ammo(int nb_ammo);
		Charger_Model*	Get_Charger_Model();
		void		Set_Charger_Model(Charger_Model* charger);

	private:
		int		__id;
		int		__nb_ammo;
		Charger_Model*	__charger_model;
};

#endif
