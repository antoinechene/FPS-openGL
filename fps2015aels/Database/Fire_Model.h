#ifndef __FIRE_MODEL_H__
#define __FIRE_MODEL_H__

#include "Ammo_Model.h"

class Fire_Model
{
	public:
		Fire_Model(char** data);
		~Fire_Model();
		int		Get_Id();
		void		Set_Id(int);
		int		Get_Nb_Fire();
		void		Set_Nb_Fire(int);
		Ammo_Model*	Get_Ammo_Type();
		void		Set_Ammo_Type(Ammo_Model*);
		void		Set_Ammo_Type_With_Id(int id);
		void		Fire();
	private:
		int		__id;
		int		__time;
		int		__nb_fire;//nombre de tir en un clique
		Ammo_Model*	__ammo_type;// type de munition
};

#endif
