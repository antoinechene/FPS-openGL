#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <vector>
#include "../Tools/Buffer.h"
#include "Network.h"
#include "Parser.h"
#include "../Objects/Vec3f.h"


class	Client
{
public:
	Client(void);
	~Client(void);
	bool			FillIp(const char* ip, const char* port);
	bool			CreateData(void);
	int			GetFd(void);
	char*			GetPseudo(void);
	char*			GetGame(void);
	int			NewConnection(char*, char*, Network*);
	void			SendMyInfo(void);
	pthread_mutex_t*	GetMutex(void);
//	void			SendData(void);
	void			SendData(Vec3f pos);
	Vec3f			TraduceData(std::vector<char*> data, size_t i);

	static const socklen_t	addrlen = sizeof(struct sockaddr_in);
	struct sockaddr_in*	addr;
	struct addrinfo*	addr_info;
	int			fd;
	int			id;
	Parser			parser;
	Buffer			read_buf;
	Buffer			write_buf;

	char*			pseudo;
	pthread_mutex_t		__buf_mutex;
};


#endif

