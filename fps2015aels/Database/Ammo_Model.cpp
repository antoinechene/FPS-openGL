#include "Ammo_Model.h"

Ammo_Model::Ammo_Model(char** tab)
{
	this->__id = atoi(tab[0]);
//	this->object = Find_Object_With_Id(atoi(tab[1]));
	this->__speed_ammo = atoi(tab[2]);
	this->__area_effect = atoi(tab[3]);
	this->__speard = atoi(tab[4]);
	this->__fire_rate = atoi(tab[5]);
}

Ammo_Model::~Ammo_Model()
{
}

int	Ammo_Model::Get_Id()
{
	return (this->__id);
}

void	Ammo_Model::Set_Id(int id)
{
	this->__id = id;
}

//Object*	Ammo_Model::Get_Object()
//{
//	return (this->__object);
//}

//void	Ammo_Model::Set_Object(Object* object)
//{
//	this->__object = object;
//}

GLfloat	Ammo_Model::Get_Speed_Ammo()
{
	return (this->__speed_ammo);
}

void	Ammo_Model::Set_Speed_Ammo(GLfloat speed)
{
	this->__speed_ammo = speed;
}

GLfloat	Ammo_Model::Get_Area_Effect()
{
	return (this->__area_effect);
}

void	Ammo_Model::Set_Area_Effect(GLfloat area_effect)
{
	this->__area_effect = area_effect;
}

GLfloat	Ammo_Model::Get_Speard()
{
	return (this->__speard);
}

void	Ammo_Model::Set_Speard(GLfloat speard)
{
	this->__speard = speard;
}

GLfloat	Ammo_Model::Get_Fire_Rate()
{
	return (this->__fire_rate);
}

void	Ammo_Model::Set_Fire_Rate(GLfloat fire_rate)
{
	this->__fire_rate = fire_rate;
}

