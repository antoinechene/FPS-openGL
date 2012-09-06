#include "Map.h"
#include <string.h>
#include <iostream>
#include "../Objects/FBXLoader.h"
#include "../Objects/Object.h"

Map::Map(int id, const char* name, const char*	filename)
{
	this->id = id;
	this->Filename = new char[strlen(filename) + 1];
	strcpy(this->Filename, filename);
	this->Filename[strlen(filename)] = '\0';

	this->Name = new char[strlen(name) + 1];
	strcpy(this->Name, name);
	this->Name[strlen(name)] = '\0';

}

Map::~Map()
{
	size_t	i;
	size_t	size;

	i = 0;
	size = this->Obj.size();

	while (i < size)
	{
		delete this->Obj[i];
		++i;
	}
	delete	this->Name;
	delete this->Filename;
}

bool	Map::Load()
{
	FBXLoader	load;
	if (load.Import(this->Filename))
	{
		std::cout<<"error to load map"<<std::endl;
		return (false);
	}
	return(true);
}

