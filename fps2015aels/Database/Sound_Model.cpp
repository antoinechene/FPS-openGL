#include <stdlib.h>
#include "Sound_Model.h"
//#include <iostream>
#include <string.h>

Sound_Model::Sound_Model(char** tab)
{
	this->__id = atoi(tab[0]);
	this->__type = atoi(tab[1]);
//	this->__file = tab[2];
	this->__file = new char[strlen(tab[2]) + 1];
	strcpy(this->__file, tab[2]);
	this->__file[strlen(tab[2])] = '\0';
}

Sound_Model::~Sound_Model()
{
}

int	Sound_Model::Get_Id()
{
	return (this->__id);
}

void	Sound_Model::Set_Id(int id)
{
	this->__id = id;
}

int	Sound_Model::Get_Type()
{
	return (this->__type);
}

void	Sound_Model::Set_Type(int type)
{
	this->__type = type;
}

char*	Sound_Model::Get_File()
{
	return (this->__file);
}

void	Sound_Model::Set_File(char* file)
{
	this->__file = new char[strlen(file) + 1];
	strcpy(this->__file, file);
	this->__file[strlen(file)] = '\0';
//	this->__file = file;
}

