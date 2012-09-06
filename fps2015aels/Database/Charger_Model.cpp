#include "Charger_Model.h"
#include <GL/glut.h>
#include "Database.h"
//#include <stdlib.h>


Charger_Model::Charger_Model(char** tab)
{
	Database*	database;

	database = Database::GetInstance();
	this->__id = atoi(tab[0]);
	this->__ammo_model = database->Get_Ammo_Model(atoi(tab[1]));
	this->__nb_ammo_max = atoi(tab[2]);
}

Charger_Model::~Charger_Model()
{
}

int	Charger_Model::Get_Id()
{
	return (this->__id);
}

void	Charger_Model::Set_Id(int id)
{
	this->__id = id;
}

int	Charger_Model::Get_Nb_Ammo()
{
	return (this->__nb_ammo_max);
}

void	Charger_Model::Set_Nb_Ammo(int nb_ammo)
{
	this->__nb_ammo_max = nb_ammo;
}

Ammo_Model*	Charger_Model::Get_Ammo_Model()
{
	return (this->__ammo_model);
}

void	Charger_Model::Set_Ammo_Model(Ammo_Model* ammo)
{
	this->__ammo_model = ammo;
}

