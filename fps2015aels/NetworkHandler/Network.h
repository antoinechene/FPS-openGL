#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <pthread.h>
#include <list>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

class	Client;

#define PENDING_QUEUE	6

class	Network
{
public:
			Network(void);
			~Network(void);
	bool		Init(void);
	bool		Accept(Client*);
	bool		Connect(Client*);
	bool		Listen(void);
	pthread_t*	GetThread(void);
public:
	bool	alive;
private:
	bool		__PrintError(const char*) const;
	void		__FillSet(fd_set*, fd_set*);
	bool		__GetNewPort(char[5]);
	void		__DoRead(fd_set*);
	bool		__DoWrite(fd_set*);
	static void*	__Routine(void*);
private:
	int			__fd;
	struct addrinfo*	__addr;
	pthread_t		__net_thread;
	pthread_mutex_t		__net_mutex;
	std::list<Client*>	__list_client;
	int			__max_fd;
	bool			__is_listening;
};


#endif

