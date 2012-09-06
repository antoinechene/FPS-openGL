//#include <iostream>
//#include <stdio.h>
#include <GL/glut.h>
#include "Weapon.h"
#include "Charger.h"
#include "Database.h"
#include "Weapon_Model.h"
#include "Charger_Model.h"
#include "Fire_Model.h"

Weapon::Weapon(Weapon_Model* weapon) 
{
	Database*	database;

	database = Database::GetInstance();
	if (weapon->Get_Charger1()->Get_Ammo_Model()->Get_Id() == weapon->Get_Charger2()->Get_Ammo_Model()->Get_Id()) 
		this->__same_ammo = true;
	else
		this->__same_ammo = false;
	this->__charger1 = new Charger(weapon->Get_Charger1());
	this->__charger2 = new Charger(weapon->Get_Charger2());
	this->__weapon_model = weapon;
}

Weapon::~Weapon()
{
}

Weapon_Model*	Weapon::Get_Weapon_Model()
{
	return (this->__weapon_model);
}

int	Weapon::Get_Id()
{
	return (this->__id);
}

Charger*	Weapon::Get_Charger1()
{
	return (this->__charger1);
}

Charger*	Weapon::Get_Charger2()
{
	return (this->__charger2);
}

void	Weapon::Fire(bool fire)
{
	int	i;

	i = 0;
	if (fire == 0)
	{
		while (i < this->__weapon_model->Get_Fire_Primary()->Get_Nb_Fire() &&
		       this->__charger1->Get_Nb_Ammo() > 0)
		{
			this->__charger1->Set_Nb_Ammo(this->__charger1->Get_Nb_Ammo() - 1);
			++i;
		}
//		if (this->__charger1->Get_Nb_Ammo() == 0 && this->__charger1 != 0)
//			this->Reload(fire);
	}
	else
	{
		if (this->__same_ammo == 1)
		{
			printf("la meme\n");
			while (i < this->__weapon_model->Get_Fire_Secondary()->Get_Nb_Fire() &&
			       this->__charger1->Get_Nb_Ammo() > 0)
			{
				this->__charger1->Set_Nb_Ammo(this->__charger1->Get_Nb_Ammo() - 1);
				++i;
			}
//			if (this->__nb_ammo1 == 0)
//				this->Reload(fire - 1);
		}
		else
		{
			printf("ou pas\n");
			while (i < this->__weapon_model->Get_Fire_Secondary()->Get_Nb_Fire() &&
			       this->__charger2->Get_Nb_Ammo() > 0)
			{
				this->__charger2->Set_Nb_Ammo(this->__charger2->Get_Nb_Ammo() - 1);
				++i;
			}
//			if (this->__nb_ammo2 == 0)
//				this->Reload(fire);
		}
	}
}

