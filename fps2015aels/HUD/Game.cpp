#include "Game.h"
#include "../map/Map.h"
#include "../Database/Player.h"


Game::Game(int id, Map* CurentMap, int
Time, int Playermax)
{
	this->id = id;
	this->CurentMap = CurentMap;
	this->TimeOfMap = Time;
	this->NBPlayerMax = Playermax;
}

Game::~Game()
{
	std::list<Player*>::iterator	it;

	it = this->PlayersList.begin();
	while (it != this->PlayersList.end())
	{
		delete *it;
		this->PlayersList.erase(it);
		++it;
	}
	delete this->CurentMap;
}


bool	Game::EndGame()
{
	if (this->TimeOfMap == 0)
		return (true);
	return (false);
}


void	Game::ActualizeTime()
{
	this->TimeOfMap --;
}

void	Game::LoadMap(void)
{
	this->CurentMap->Load();
}
