#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <vector>
#include <time.h>
#include "Network.h"
#include "Client.h"
#include "DataNetwork.h"
#include "DataGame.h"
#include "DataPlayer.h"

Network::Network(void) : __fd(0), __addr(NULL), __max_fd(1), __is_listening(false)
{
}


Network::~Network(void)
{
	Client*	cl;

	while (!this->__list_client.empty())
	{
		cl = this->__list_client.front();
		this->__list_client.pop_front();
		delete cl;
	}
	freeaddrinfo(this->__addr);
	if (this->__fd > 0)
		close(this->__fd);
}

bool	Network::Connect(Client* client)
{
	client->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client->fd == -1)
		return (this->__PrintError("Connect:socket"));
	if (connect(client->fd, (sockaddr*)client->addr, client->addrlen) == -1)
	{
		perror("Connect");
		return (false);
	}
	this->__list_client.push_back(client);
	if (client->fd > this->__max_fd)
		this->__max_fd = client->fd;
	return (true);
}

bool	Network::Accept(Client* info)
{
//	int		nsend;
	Client*		client;
	socklen_t	size;

	DataNetwork*	Data;
	DataGame*	Game;
	DataPlayer*	Player;

	client = new (std::nothrow) Client;
	if (client == NULL)
		return (false);
	size = sizeof(client->addr);
	client->fd = accept(this->__fd, (sockaddr*)client->addr, &size);
	if (client->fd == -1 ||
	    (info != NULL &&
	     ((struct sockaddr_in*)&client->addr)->sin_addr.s_addr !=
	     ((struct sockaddr_in*)&info->addr)->sin_addr.s_addr))
	{
		delete client;
		return (false);
	}
	if (pthread_mutex_lock(&(client->__buf_mutex)) != 0)
	{
		std::cout << "error with mutex" << std::endl;
		return (false);
	}
	client->write_buf.AddStr("/INFO\nBienvenu sur le server FPS\n/END\n", 39);
	pthread_mutex_unlock(&(client->__buf_mutex));

	this->__list_client.push_back(client);
	Data = DataNetwork::GetInstance();
	Game = Data->FoundGame((char*)"SERVER");
	Player = new DataPlayer();
	Player->SetFd(client->GetFd());
	Player->SetPseudo((char*)"pseudo");
	Game->AddPlayer(Player);

	if (client->fd > this->__max_fd)
		this->__max_fd = client->fd;
	return (true);
}

bool	Network::Listen(void)
{
	if (pthread_mutex_lock(&this->__net_mutex) != 0)
		return (false);
	this->__is_listening = true;
	if (listen(this->__fd, PENDING_QUEUE) == -1)
	{
		pthread_mutex_unlock(&this->__net_mutex);
		return (false);
	}
	pthread_mutex_unlock(&this->__net_mutex);
	return (true);
}

pthread_t*	Network::GetThread(void)
{
	return (&this->__net_thread);
}

bool	Network::Init(void)
{
	struct addrinfo		hints;
	char			port[5];
	int			bind_res;
	DataNetwork*		Data;

	Data = DataNetwork::GetInstance();
	Data->SetClientsList(&this->__list_client);

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	bind_res = -1;
	strcpy(port, "2300");
	while (bind_res == -1)
	{
		if (getaddrinfo(NULL, port, &hints, &this->__addr) != 0)
			return (this->__PrintError("Init:getaddrinfo"));
		this->__fd = socket(this->__addr->ai_family,
				    this->__addr->ai_socktype,
				    this->__addr->ai_protocol);
		if (this->__fd == -1)
			return (this->__PrintError("Init:socket"));
		this->__max_fd = this->__fd;
		bind_res = bind(this->__fd, this->__addr->ai_addr, this->__addr->ai_addrlen);
		if (bind_res == -1)
		{
			if (errno == EADDRINUSE)
			{
				this->__GetNewPort(port);
				close(this->__fd);
				freeaddrinfo(this->__addr);
			}
			else
				return (this->__PrintError("Init:bind"));
		}
	}
	pthread_mutex_init(&this->__net_mutex, NULL);
	pthread_create(&this->__net_thread, NULL, &this->__Routine, this);
	std::cout << port << std::endl;
	return (true);
}

bool	Network::__GetNewPort(char port[5])
{
	if (strcmp(port, "2400") == 0)
		return (false);
	port[3]++;
	if (port[3] > '9')
	{
		port[3] = '0';
		port[2]++;
		if (port[2] > '9')
		{
			port[2] = '0';
			port[1]++;
		}
	}
	return (true);
}



void	Network::__DoRead(fd_set* set)
{
	DataNetwork*				Data;
	DataGame*				Game;
	DataPlayer*				Player;

	std::list<Client*>::iterator		it;
	const std::list<Client*>::iterator	end = this->__list_client.end();

	it = this->__list_client.begin();
	while (it != end)
	{
		if (FD_ISSET((*it)->fd, set))
		{
			ssize_t	nbrecv;
			nbrecv = (*it)->read_buf.RecvEntry((*it)->fd, 200);
			if (nbrecv <= 0)
			{
				delete *it;
				it = this->__list_client.erase(it);
				--this->__max_fd;
				continue ;
			}
			else if ((*it)->CreateData() == true)
			{
				Data = DataNetwork::GetInstance();
				Game = Data->FoundGame((*it)->fd);
				Player = Data->FoundPlayer((*it)->fd);
#ifdef _SERVER
				(*it)->parser.Server_CheckData(Player, Game->GetPlayers());
#else
				(*it)->parser.Client_CheckData(Player);
#endif
			}
		}
		++it;
	}
}


void	Network::__FillSet(fd_set* read_set, fd_set* write_set)
{
	std::list<Client*>::iterator	it;
	std::list<Client*>::iterator	it_end;

	it = this->__list_client.begin();
	it_end = this->__list_client.end();
	while (it != it_end)
	{
		if ((*it)->write_buf.GetSize() != 0)
		{
			FD_SET((*it)->fd, write_set);
		}
		else
			FD_SET((*it)->fd, read_set);
		++it;
	}
	FD_SET(this->__fd, read_set);
}

bool	Network::__DoWrite(fd_set* set)
{
	std::list<Client*>::iterator		it;
	const std::list<Client*>::iterator	end = this->__list_client.end();
	ssize_t					nwrite;
	char*					str;

	it = this->__list_client.begin();
	while (it != end)
	{
		if (FD_ISSET((*it)->fd, set))
		{
			if (pthread_mutex_lock((*it)->GetMutex()) != 0)
			{
				std::cout << "error with mutex lock 1" << std::endl;
				return (false);
			}
			str = (*it)->write_buf.Flush();
			pthread_mutex_unlock((*it)->GetMutex());
			if (str == NULL)
				return (false);
			nwrite =
			send((*it)->fd, str, strlen(str) + 1, 0);
			if (nwrite <= 0)
			{
				delete *it;
				delete str;
				this->__list_client.erase(it);
				--this->__max_fd;
			}
			else if (nwrite < (ssize_t)strlen(str))
			{
				if (pthread_mutex_lock((*it)->GetMutex()) != 0)
				{
					std::cout << "error with mutex lock 2" << std::endl;
					return (false);
				}
				(*it)->write_buf.AddStr(str + nwrite, strlen(str) - nwrite);
				pthread_mutex_unlock((*it)->GetMutex());
				delete str;
			}
		}
		++it;
	}
	return (true);
}

void*	Network::__Routine(void* data)
{
	fd_set		read_set;
	fd_set		write_set;
	struct timeval	tv;
	Network*	net;
	int		ret;

	net = (Network*)data;
	net->alive = true;
	while (net->alive)
	{
		tv.tv_sec = 0;
		tv.tv_usec = 1000;
		FD_ZERO(&read_set);
		FD_ZERO(&write_set);
		if (pthread_mutex_lock(&net->__net_mutex) != 0)
		{
			pthread_mutex_unlock(&net->__net_mutex);
			return ((void*)-1);
		}
		net->__FillSet(&read_set, &write_set);
		ret = select(net->__max_fd + 1, &read_set, &write_set, NULL, &tv);
		if (ret == -1)
		{
			pthread_mutex_unlock(&net->__net_mutex);
			return ((void*)-1);
		}
		if (ret > 0)
		{
			if (FD_ISSET(net->__fd, &read_set) && net->__is_listening == true)
				net->Accept(NULL);
			net->__DoRead(&read_set);
			net->__DoWrite(&write_set);
		}
		pthread_mutex_unlock(&net->__net_mutex);
		
	}
	return (data);
}

bool	Network::__PrintError(const char* fct) const
{
	(void)fct;
	return (false);
}
