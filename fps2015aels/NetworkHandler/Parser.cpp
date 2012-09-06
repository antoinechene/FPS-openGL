#include <string.h>
#include <iostream>
#include <new>
#include <vector>
#include <stdlib.h>
#include "Parser.h"
#include "Client.h"
#include "DataNetwork.h"
#include "DataGame.h"
#include "DataPlayer.h"



Parser::Parser(void)
{
}

Parser::~Parser(void)
{

}

bool	Parser::Parse(char* str)
{
	char*	response;

	response = new (std::nothrow) char[200];
	if (response == NULL)
		return (false);
	if (strcmp(str, "42\n") == 0)
		this->resp_list.push_back(Parser::OK);
	return (true);
}

bool	Parser::CompareTics(char*)
{
	return (true);
}

Client*	Parser::GetClient(std::list<Client*>* list, int fd)
{
	std::list<Client*>::iterator	it;
	std::list<Client*>::iterator	end;

	it = list->begin();
	end = list->end();
	while (it != end)
	{
		if ((*it)->GetFd() == fd)
			return (*it);
		++it;
	}
	return (NULL);
}

void	Parser::TransmitDataToAll(DataPlayer* cli, size_t i)
{
	int				begin;
	DataNetwork*			data;
	std::list<Client*>*		client;
	std::list<Client*>::iterator	it;
	std::list<Client*>::iterator	end;
	std::vector<char*>		tab;

	data = DataNetwork::GetInstance();
	client = data->GetClientsList();
	it = client->begin();
	end = client->end();
	begin = i;
	tab = *(cli->GetData());
	while (it != end)
	{
		if ((*it)->GetFd() == cli->GetFd())
		{
			++it;
			if (it == client->end())
				break;
			i = begin;
		}
		while (i < tab.size())
		{
			if (pthread_mutex_lock(&((*it)->__buf_mutex)) != 0)
			{
				std::cout << "error with mutex lock" << std::endl;
				return;
			}
			(*it)->write_buf.AddStr(tab[i], strlen(tab[i]) + 1);
			pthread_mutex_unlock(&((*it)->__buf_mutex));
			++i;
		}
		i = begin;
		++it;
	}
}

void	Parser::TransmitData(DataPlayer* cli, std::list<DataPlayer*>* list, size_t begin)
{
	DataNetwork*				data_net;
	Client*					client;
	std::list<DataPlayer*>::iterator	it;
	std::list<DataPlayer*>::iterator	end = list->end();
	std::vector<char*>*			data;
	size_t					i;
	char*					com = NULL;


	if (list->size() <= 1)
	{
		return;
	}

	data_net = DataNetwork::GetInstance();
	i = begin;
	it = list->begin();
	data = cli->GetData();
	while (it != end)
	{
		if ((*it)->GetFd() == cli->GetFd())
		{
			++it;
			if (it == end)
				break;
			i = begin;
		}
		com = new char[1000];
		client = data_net->FoundClient((*it)->GetFd());
		while (i < data->size())
		{
			com = strcat(com, (*data)[i]);
			com = strcat(com, "\n");
			++i;
		}
		if (pthread_mutex_lock(client->GetMutex()) != 0)
		{
			std::cout << "error with mutex lock" << std::endl;
			return;
		}
		client->write_buf.AddStr(com, strlen(com) + 1);
		pthread_mutex_unlock(client->GetMutex());
		delete[] com;
		i = begin;
		++it;
	}
}

void	Parser::TransmitInfoPlayers(DataPlayer* cli, std::list<DataPlayer*>* list)
{
(void)list;
	DataNetwork*				Data;
	char*					pseudo;
	std::list<Client*>::iterator	it;
	std::list<Client*>::iterator	end;
	Client*					client;
	std::list<Client*>*			listcli;
	DataPlayer*				player;

	Data = DataNetwork::GetInstance();
	listcli = Data->GetClientsList();
	if (listcli->size() <= 1)
		return;
	pseudo = NULL;
	pseudo = new char[1000];
	it = listcli->begin();
	end = listcli->end();
	client = this->GetClient(listcli, cli->GetFd());
	pseudo = strcat(pseudo, "/INFO_PLAYERS\n");
	while (it != end)
	{
		if ((*it)->GetFd() == cli->GetFd())
		{
			++it;
			if (it == end)
				break;
		}
		player = Data->FoundPlayer((*it)->GetFd());
		pseudo = strcat(pseudo, player->GetPseudo());
		pseudo = strcat(pseudo, "\n");
		++it;
	}
	pseudo = strcat(pseudo, "/END\n");
	if (pthread_mutex_lock(&(client->__buf_mutex)) != 0)
	{
		std::cout << "error with mutex lock" << std::endl;
		return;
	}
	client->write_buf.AddStr(pseudo, strlen(pseudo) + 1);
	pthread_mutex_unlock(&(client->__buf_mutex));
	delete [] pseudo;
}

void	Parser::TransmitInfoGames(DataPlayer* cli)
{
	std::list<DataGame*>::iterator	it;
	std::list<DataGame*>::iterator	end;
	DataNetwork*			Data;
	char*				game;
	std::list<Client*>*		listcli;
	Client*				client;

	Data = DataNetwork::GetInstance();
	if (Data->GetGames()->size() <= 1)
		return;
	game = new char[1000];
	listcli = Data->GetClientsList();
	it = Data->GetGames()->begin();
	end = Data->GetGames()->end();
	client = this->GetClient(listcli, cli->GetFd());
	game = strcpy(game, "/INFO_GAMES\n");

	while (it != end)
	{
		game = strcat(game, (*it)->GetID());
		game = strcat(game, "\n");
		++it;
	}
	game = strcat(game, "/END\n");
	if (pthread_mutex_lock(&(client->__buf_mutex)) != 0)
	{
		std::cout << "error with mutex lock" << std::endl;
		return;
	}
	client->write_buf.AddStr(game, strlen(game) + 1);
	pthread_mutex_unlock(&(client->__buf_mutex));
	delete[] game;
}


void	Parser::Server_CheckData(DataPlayer* cli, std::list<DataPlayer*>* list)
{
	size_t				i;
	std::vector<char*>		Data;

	i = 0;
	Data = *(cli->GetData());
	while (i < Data.size())
	{
		if (strcmp(Data[i], "/TIC") == 0)
		{
		//	if (!this->CompareTics(Data[i + 1]))
		//		i = i;
		}
		if (strcmp(Data[i], "/MY_INFO") == 0)
		{
			cli->SetPseudo(Data[i + 1]);
		//	this->TransmitDataToAll(cli, i);
		}
		if (strcmp(Data[i], "/INFO_PLAYERS") == 0)
		{
			this->TransmitInfoPlayers(cli, list);
		}
		if (strcmp(Data[i], "/INFO_GAMES") == 0)
		{
			this->TransmitInfoGames(cli);
		}
		if (strcmp(Data[i], "/DATA") == 0)
		{
			this->TransmitData(cli, list, i);
			break;
		}
		else if (strcmp(Data[i], "/TALK") == 0)
		{
			this->TransmitData(cli, list, i);
			break;
		}
		else if (strcmp(Data[i], "/TALKTO") == 0)
		{
			this->TransmitData(cli, list, i);
			break;
		}
		//else if (strcmp(Data[i], "/END") == 0)
		//{
		//	this->ClearData(&Data);
		//	return;
		//}
		++i;
	}
	cli->ClearData();
}


void	Parser::Client_CheckData(DataPlayer* cli)
{
	size_t				i;
	size_t				j;
	std::vector<char*>		Data;
	DataNetwork*			data;
	DataGame*			game;
	DataPlayer*			player;

	i = 0;
	Data = *(cli->GetData());
	while (i < Data.size())
	{
		if (strcmp(Data[i], "/TIC") == 0)
		{
		}
		if (strcmp(Data[i], "/MY_INFO") == 0)
		{
			data = DataNetwork::GetInstance();
			player = new DataPlayer();
			player->SetPseudo(Data[i + 1]);
			game = data->FoundGame((char*)"SERVER");
			game->AddPlayer(player);
		}
		if (strcmp(Data[i], "/INFO") == 0)
		{
		}
		if (strcmp(Data[i], "/INFO_PLAYERS") == 0)
		{
			j = i;

			while (j < Data.size())
			{
				++j;
			}
			
		}
		if (strcmp(Data[i], "/INFO_GAMES") == 0)
		{
			j = i;
			while (j < Data.size())
			{
				++j;
			}
			
		}
		if (strcmp(Data[i], "/DATA") == 0)
		{
			this->ShowData(cli);
		}
		if (strcmp(Data[i], "/TALK") == 0)
		{
			this->ShowMessage(cli, i + 1);
		}
		if (strcmp(Data[i], "/TALKTO") == 0)
		{
			this->ShowMessageTo(cli, i + 1);
		}
		//if (strcmp(Data[i], "/END") == 0)
		//{
		//	this->ClearData(&Data);
		//	return;
		//}
		++i;
	}
	cli->ClearData();
}

void	Parser::__SaveBuf(char* str)
{
	(void)str;
}

void	Parser::ShowData(DataPlayer* cli)
{
	size_t			i;
	std::vector<char*>*	Data;

	Data = cli->GetData();
	i = 0;
	while (i < Data->size())
	{
		++i;
	}
}

void	Parser::ShowMessage(DataPlayer* cli, int begin)
{
	size_t			i;
	std::vector<char*>	Data;


	i = begin;
	Data = *(cli->GetData());
	while (i < Data.size())
	{
		if (Data[i][0] == '/')
			break;
		++i;
	}
}

void	Parser::ShowMessageTo(DataPlayer* cli, int begin)
{
	size_t			i;
	std::vector<char*>	Data;


	if (cli->GetFd() != atoi(Data[begin]))
		return;
	i = begin + 1;
	Data = *(cli->GetData());
	while (i < Data.size())
	{
		if (Data[i][0] == '/')
			break;
		++i;
	}
}







