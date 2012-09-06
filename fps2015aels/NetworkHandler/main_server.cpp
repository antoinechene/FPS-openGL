#include <unistd.h>
#include <pthread.h>
#include "Network.h"


int	main(void)
{
	Network	net;

	if (!net.Init())
		return (-1);
	if (!net.Listen())
		return (-1);
	pthread_join(*(net.GetThread()), NULL);
	//while (net.alive);
	//sleep(30);
	//net.alive = false;
	sleep(1000000);
	return (0);
}
