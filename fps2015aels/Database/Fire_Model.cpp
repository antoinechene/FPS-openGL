#include "Fire_Model.h"
#include "Database.h"

Fire_Model::Fire_Model(char** tab)
{
	Database*	database;

	database = Database::GetInstance();
	this->__id = atoi(tab[0]);
	this->__ammo_type = database->Get_Ammo_Model(atoi(tab[1]));
	this->__nb_fire = atoi(tab[2]);
	this->__time = atoi(tab[3]);
}

Fire_Model::~Fire_Model()
{

}

int	Fire_Model::Get_Id()
{
	return (this->__id);
}

void	Fire_Model::Set_Id(int id)
{
	this->__id = id;
}

int	Fire_Model::Get_Nb_Fire()
{
	return (this->__nb_fire);
}

void	Fire_Model::Set_Nb_Fire(int fire)
{
	this->__nb_fire = fire;
}

Ammo_Model*	Fire_Model::Get_Ammo_Type()
{
	return (this->__ammo_type);
}

void	Fire_Model::Set_Ammo_Type(Ammo_Model* type)
{
	this->__ammo_type = type;
}

void	Fire_Model::Set_Ammo_Type_With_Id(int id)
{
	Database*	database;

	database = Database::GetInstance();
	this->__ammo_type = database->Get_Ammo_Model(id);
}

void	Fire_Model::Fire()
{
	
}
