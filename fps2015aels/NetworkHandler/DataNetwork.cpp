#include "DataNetwork.h"
#include "DataGame.h"
#include "DataPlayer.h"
#include "Client.h"

DataNetwork::DataNetwork()
{
	DataGame*	data;

	data = new DataGame();
	data->SetID((char*)"SERVER");
	this->__games.push_back(data);
}

DataNetwork::~DataNetwork()
{
	this->__games.clear();
}

std::list<DataGame*>*	DataNetwork::GetGames(void)
{
	return (&this->__games);
}


void	DataNetwork::InitDataClient(Client* cli)
{
	DataGame*	Game;
	DataPlayer*	Player;

	Game = this->FoundGame((char*)"SERVER");
	Player = new DataPlayer();
	Player->SetFd(cli->GetFd());
	Player->SetPseudo((char*)"fabien");
	Game->AddPlayer(Player);

}


void	DataNetwork::AddGame(DataGame* game)
{
	this->__games.push_back(game);
}

DataGame*	DataNetwork::FoundGame(char* name)
{
	std::list<DataGame*>::iterator	it;
	std::list<DataGame*>::iterator	end;

	it = this->__games.begin();
	end = this->__games.end();

	while (it != end)
	{
		if (strcmp(name, (*it)->GetID()) == 0)
		{
			std::cout << "Game: " << (*it)->GetID() << " found" << std::endl;
			return (*it);
		}
		++it;
	}
	std::cout << "Game not found" << std::endl;
	return (NULL);
}


DataGame*	DataNetwork::FoundGame(int fd)
{
	std::list<DataGame*>::iterator		it_game;
	std::list<DataGame*>::iterator		end_game;
	std::list<DataPlayer*>::iterator	it_player;
	std::list<DataPlayer*>::iterator	end_player;

	it_game = this->__games.begin();
	end_game = this->__games.end();
	while (it_game != end_game)
	{
		it_player = (*it_game)->GetPlayers()->begin();
		end_player = (*it_game)->GetPlayers()->end();
		while (it_player != end_player)
		{
			if (fd == (*it_player)->GetFd())
				return (*it_game);
			++it_player;
		}
		++it_game;

	}
	return NULL;
}

DataPlayer*	DataNetwork::FoundPlayer(int fd)
{
	std::list<DataGame*>::iterator		it_game;
	std::list<DataGame*>::iterator		end_game;
	std::list<DataPlayer*>::iterator	it_player;
	std::list<DataPlayer*>::iterator	end_player;

	it_game = this->__games.begin();
	end_game = this->__games.end();
	while (it_game != end_game)
	{
		it_player = (*it_game)->GetPlayers()->begin();
		end_player = (*it_game)->GetPlayers()->end();
		while (it_player != end_player)
		{
			if (fd == (*it_player)->GetFd())
				return (*it_player);
			++it_player;
		}
		++it_game;

	}
	return NULL;
}

Client*	DataNetwork::FoundClient(int fd)
{
	std::list<Client*>::iterator	it;
	std::list<Client*>::iterator	end;

	it = this->__clients->begin();
	end = this->__clients->end();
	while (it != end)
	{
		if (fd == (*it)->fd)
			return (*it);
		++it;
	}
	std::cout << " client not found" << std::endl;
	return (NULL);
}

void	DataNetwork::SetClientsList(std::list<Client*>* cli)
{
	this->__clients = cli;
}


std::list<Client*>*	DataNetwork::GetClientsList(void)
{
	return (this->__clients);
}
