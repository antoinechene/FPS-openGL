#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <netinet/in.h>

int	main(void)
{
	struct addrinfo		hints;
	struct addrinfo*	res;
//	int			fd;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo("ryu", NULL, &hints, &res) != 0)
		return (-1);
	if (res == NULL)
		std::cout << "NULL" << std::endl;
	while (res != NULL)
	{
		std::cout << "ai_flags : " << res->ai_flags << std::endl
			  << "ai_family : " << res->ai_family << std::endl
			  << "ai_socktype : " << res->ai_socktype << std::endl
			  << "ai_protocol : " << res->ai_protocol << std::endl
			  << "ai_addrlen : " <<	res->ai_addrlen << std::endl;
		std::cout << "Ip : "
			  << ((struct sockaddr_in*)res->ai_addr)->sin_addr.s_addr << std::endl
			  << (int)(unsigned char)((((struct sockaddr_in*)res->ai_addr)->sin_addr.s_addr) & 0xff) << ":"
			  << (int)(unsigned char)(((((struct sockaddr_in*)res->ai_addr)->sin_addr.s_addr) >> 8) & 0xff) << ":"
			  << (int)(unsigned char)(((((struct sockaddr_in*)res->ai_addr)->sin_addr.s_addr) >> 16) & 0xff) << ":"
			  << (int)(unsigned char)(((((struct sockaddr_in*)res->ai_addr)->sin_addr.s_addr) >> 24) & 0xff) << std::endl;
		res = res->ai_next;
	}
	std::cout << (unsigned int)(uint32_t)(gethostbyname("ryu")->h_addr[0]) << std::endl
		  << (unsigned int)(uint32_t)(gethostbyname("ryu")->h_addr[1]) << std::endl
		  << (unsigned int)(uint32_t)(gethostbyname("ryu")->h_addr[2]) << std::endl
		  << (unsigned int)(uint32_t)(gethostbyname("ryu")->h_addr[3]) << std::endl;
	return (0);
}
