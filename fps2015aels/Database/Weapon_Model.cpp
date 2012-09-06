#include "Weapon_Model.h"
#include <GL/glut.h>
#include "Database.h"
#include "Fire_Model.h"
//#include <stdlib.h>

Weapon_Model::Weapon_Model(char** tab)
{
	Database*	database;

	database = Database::GetInstance();
	this->__id = atoi(tab[0]);
///////	this->object = Find_Object_With_Id(atoi(tab[1]));
	this->__primary_fire = database->Get_Fire_Model(atoi(tab[2]));
	this->__secondary_fire = database->Get_Fire_Model(atoi(tab[3]));
	this->__charger1 = database->Get_Charger_Model(atoi(tab[4]));
	this->__charger2 = database->Get_Charger_Model(atoi(tab[5]));
	this->__nb_charger1 = atoi(tab[6]);
	this->__nb_charger2 = atoi(tab[7]);
	this->__auto = atoi(tab[8]);
}

Weapon_Model::~Weapon_Model()
{
}

int	Weapon_Model::Get_Id()
{
	return (this->__id);
}

void	Weapon_Model::Set_Id(int id)
{
	this->__id = id;
}

int	Weapon_Model::Get_Nb_Charger1()
{
	return (this->__nb_charger1);
}

void	Weapon_Model::Set_Nb_Chargeur1(int charger1)
{
	this->__nb_charger1 = charger1;
}

int	Weapon_Model::Get_Nb_Charger2()
{
	return (this->__nb_charger2);
}

void	Weapon_Model::Set_Nb_Charger2(int charger2)
{
	this->__nb_charger2 = charger2;
}
/*
///////////void	Weapon_Model::Set_Object(Object* object)
////////{
///////	this->object = object;
///////}

///////Object*	Weapon_Model::Get_Object()
/////{
/////	return (this->object);
/////}
*/
Fire_Model*	Weapon_Model::Get_Fire_Primary()
{
	return (this->__primary_fire);
}

void	Weapon_Model::Set_Fire_Primary(Fire_Model* fire)
{
	this->__primary_fire = fire;
}

void	Weapon_Model::Set_Fire_Primary_With_Id(int id)
{
	Database*	database;

	database = Database::GetInstance();
	this->__primary_fire = database->Get_Fire_Model(id);
}

Fire_Model*	Weapon_Model::Get_Fire_Secondary()
{
	return (this->__secondary_fire);
}

void	Weapon_Model::Set_Fire_Secondary(Fire_Model* fire)
{
	this->__secondary_fire = fire;
}

void	Weapon_Model::Set_Fire_Secondary_With_Id(int id)
{
	Database*	database;

	database = Database::GetInstance();
	this->__secondary_fire = database->Get_Fire_Model(id);
}

Charger_Model*	Weapon_Model::Get_Charger1()
{
	return (this->__charger1);
}

Charger_Model*	Weapon_Model::Get_Charger2()
{
	return (this->__charger2);
}

