#include <iostream>
#include <string.h>
#include "DataGame.h"
#include "DataPlayer.h"

DataGame::DataGame()
{
	this->__ID = NULL;
}

DataGame::~DataGame()
{
	if (this->__ID == NULL)
		return;
	delete[] this->__ID;
}

void	DataGame::AddPlayer(DataPlayer* player)
{
	this->__players.push_back(player);
}

void	DataGame::SetID(char* id)
{
	if (this->__ID != NULL)
		delete[] this->__ID;
	this->__ID = new char[strlen(id) + 1];
	strcpy(this->__ID, id);
}

char*	DataGame::GetID(void)
{
	return (this->__ID);
}

std::list<DataPlayer*>*	DataGame::GetPlayers(void)
{
	return (&this->__players);
}
