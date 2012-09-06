#include "Player.h"
#include "Database.h"
#include "Weapon.h"
#include "Weapon_Model.h"
#include "Charger_Model.h"
#include "Charger.h"
#include "../Objects/Display.h"
#include "../HUD/Hud.h"
//#include <stdio.h>

Player::Player(const char* pseudo, char* file_avatar, int id, Vec3f, Vec3f, Vec3f, Vec3f, GLfloat)
{
	Weapon*				weapon;
	Database*			database;
	std::list<Weapon*>::iterator	it;

	database = Database::GetInstance();
	this->__hp = 100;
	this->__avatar = file_avatar;
	this->__id = id;
	this->__nb_kill = 0;
	this->__nb_dead = 0;
	this->__pseudo = (char*)pseudo;
	weapon = new Weapon(database->Get_Weapon_Model(1));
	this->__list_weapon.push_back(weapon);
	this->__weapon = this->__list_weapon.begin();
	this->__list_charger.resize(database->__charger_db.size(), 0);
	it = this->__list_weapon.begin();
	while (it != this->__list_weapon.end())
	{
		this->__list_charger[(*it)->Get_Weapon_Model()->Get_Charger1()->Get_Id()] = (*it)->Get_Weapon_Model()->Get_Nb_Charger1();
		this->__list_charger[(*it)->Get_Weapon_Model()->Get_Charger2()->Get_Id()] = this->__list_charger[(*it)->Get_Weapon_Model()->Get_Charger2()->Get_Id()] + (*it)->Get_Weapon_Model()->Get_Nb_Charger2();
		++it;
	}
}

Player::~Player() 
{
}

//void	Player::Set_Object(Object* object)
//{
//	this->__object = object;
//}

//Object*	Player::Get_Object()
//{
//	return (this->__object);
//}

void	Player::Add_Weapon(int id)
{
	Weapon*		weapon;
	Database*	database;

	database = Database::GetInstance();
	weapon = new Weapon(database->Get_Weapon_Model(id));
	this->__list_weapon.push_back(weapon);
}

void	Player::Delete_Weapon(int id)
{
	std::list<Weapon*>::iterator	it;

	it = this->__list_weapon.begin();
	while (it != this->__list_weapon.end())
	{
		if ((*it)->Get_Weapon_Model()->Get_Id() == id)
			it = this->__list_weapon.erase(it);
		else
			it++;
	}
}

std::list<Weapon*>	Player::Get_List_Weapon()
{
	return (this->__list_weapon);
}

std::vector<int>	Player::Get_Vector_Charger()
{
	return (this->__list_charger);
}

Weapon*	Player::Get_Weapon()
{
	return (*this->__weapon);
}

void	Player::Fire(bool fire)
{
	Display*	disp;

	disp = Display::GetInstance();
//	disp->hud->Set_Ammo1(this->Get_Weapon()->Get_Charger1()->Get_Nb_Ammo());
	(*this->__weapon)->Fire(fire);
	disp->hud->Set_Ammo1(this->Get_Weapon()->Get_Charger1()->Get_Nb_Ammo());
}

void	Player::Reload(bool charger)
{
	int	id_ammo1;
	int	id_ammo2;
	Display*	disp;

	disp = Display::GetInstance();

	id_ammo1 = (*this->__weapon)->Get_Weapon_Model()->Get_Charger1()->Get_Id();
	id_ammo2 = (*this->__weapon)->Get_Weapon_Model()->Get_Charger2()->Get_Id();
	if (this->__list_charger[id_ammo1] > 0 && charger == 0)
	{
		--this->__list_charger[id_ammo1];
		(*this->__weapon)->Get_Charger1()->Set_Nb_Ammo((*this->__weapon)->Get_Charger1()->Get_Charger_Model()->Get_Nb_Ammo());
		disp->hud->Set_Ammo1(this->Get_Weapon()->Get_Charger1()->Get_Nb_Ammo());
		disp->hud->Set_Charger1(this->Get_Nb_Charger1());
	}
	if (this->__list_charger[id_ammo2] > 0 && charger == 1)
	{
		--this->__list_charger[id_ammo2];
		(*this->__weapon)->Get_Charger2()->Set_Nb_Ammo((*this->__weapon)->Get_Charger2()->Get_Charger_Model()->Get_Nb_Ammo());
		disp->hud->Set_Ammo2(this->Get_Weapon()->Get_Charger2()->Get_Nb_Ammo());
		disp->hud->Set_Charger2(this->Get_Nb_Charger2());
	}
}

void	Player::Add_Charger(Charger_Model* charger)
{
	this->__list_charger[charger->Get_Id()] = this->__list_charger[charger->Get_Id()] + charger->Get_Nb_Ammo();
}

int	Player::Get_Nb_Charger1()
{
	return (this->__list_charger[(*this->__weapon)->Get_Weapon_Model()->Get_Charger1()->Get_Id()]);
}

int	Player::Get_Nb_Charger2()
{
	return (this->__list_charger[(*this->__weapon)->Get_Weapon_Model()->Get_Charger2()->Get_Id()]);
}

bool	Player::GenerateHitBox(void)
{
	return (true);
}

int	Player::Get_Life()
{
	return (this->__hp);
}

void	Player::Set_Life(int life)
{
	this->__hp = life;
}

int	Player::Get_Nb_Kill()
{
	return (this->__nb_kill);
}

void	Player::Set_Nb_Kill(int kill)
{
	this->__nb_kill = kill;
}

char*	Player::Get_Avatar()
{
	return (this->__avatar);
}
