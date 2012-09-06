#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <list>
#include <vector>
#include "../Objects/Vec3f.h"

class Weapon;
class Charger_Model;

class Player
{
	public:
		Player(const char* pseudo, char* file_avatar, int id, Vec3f, Vec3f, Vec3f, Vec3f, GLfloat);
		~Player();
//		void			Set_Object(Object* object);
//		Object*			Get_Object();
		void			Add_Weapon(int id);
		void			Delete_Weapon(int id);
		std::list<Weapon*>	Get_List_Weapon();
		std::vector<int>	Get_Vector_Charger();
		Weapon*			Get_Weapon();
		int			Get_Life();
		void			Set_Life(int life);
		int			Get_Nb_Kill();
		int			Get_Nb_Charger1();
		int			Get_Nb_Charger2();
		void			Set_Nb_Kill(int kill);
		char*			Get_Avatar();
		void			Fire();
		void			Reload(bool charger);
		void			Add_Charger(Charger_Model*);
		void			Fire(bool);
		virtual bool	GenerateHitBox(void);

//	private:
		int				__hp;
		int				__id;
		int				__nb_kill;
		int				__nb_dead;
		char*				__pseudo;
		char*				__avatar;
//		Object*				__object;
//	public:
		std::vector<int>		__list_charger;
		std::list<Weapon*>		__list_weapon;
		std::list<Weapon*>::iterator	__weapon;
};

#endif
