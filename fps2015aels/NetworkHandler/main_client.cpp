#include <time.h>
#include <iostream>
#include "Client.h"
#include "Network.h"


int	main(int argc, char** argv)
{
	Client	cli;
	Network	net;
	int	ret;

	(void)argc;

	ret = cli.NewConnection(argv[1], argv[2], &net);
	if (ret == 0)
		pthread_join(*(net.GetThread()), NULL);
	return(0);
}

