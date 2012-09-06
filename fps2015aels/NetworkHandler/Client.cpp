#include <string.h>
#include "Network.h"
#include "Client.h"
#include "DataNetwork.h"
#include "DataPlayer.h"

char*	FloatToChar(float f)
{
	char*	com;

	com = new char[20];
	sprintf(com, "%f" , f);
	return (com);
}


Client::Client(void) : addr(NULL), fd(0)
{

	this->read_buf.NewBuffer(2000);
	this->write_buf.NewBuffer(2000);
	pthread_mutex_init(&this->__buf_mutex, NULL);
}

Client::~Client(void)
{
	if (fd > 0)
		close(this->fd);
	if (addr != NULL)
		freeaddrinfo(this->addr_info);
}


Vec3f	Client::TraduceData(std::vector<char*> data, size_t i)
{
	Vec3f	pos;

	//pos = new Vec3f();

	pos[0] = atof(data[i + 1]);
	pos[1] = atof(data[i + 2]);
	pos[2] = atof(data[i + 3]);
	return (pos);
}

int	Client::NewConnection(char* ip, char* port, Network* net){
	Client*		client;
	DataNetwork*	Data;

	client = new Client();
	if (!net->Init())
	{
		std::cout << "Fail Init net\n";
		return (-1);
	}
	if (!client->FillIp(ip, port))
	{
		std::cout << "Fail Filling ip\n";
		return (-1);
	}
	if (!net->Connect(client))
	{
		std::cout << "Fail Connect\n";
		return (-1);
	}
	Data = DataNetwork::GetInstance();

	Data->InitDataClient(client);
	client->SendMyInfo();

	return (0);
}


void	Client::SendData(Vec3f pos)
{
	char*	com;
	char*	fx;
	char*	fy;
	char*	fz;


	com = new char[1000];


	fx = FloatToChar(pos[0]);
	fy = FloatToChar(pos[1]);
	fz = FloatToChar(pos[2]);


	com = strcpy(com, "/DATA\n");
	com = strcat(com, fx);
	com = strcat(com, fy);
	com = strcat(com, fz);
	com = strcat(com, "/END\n");
	if (pthread_mutex_lock(&this->__buf_mutex) != 0)
	{
		std::cout << "error with mutex lock" << std::endl;
		return;
	}
	this->write_buf.AddStr(com, strlen(com) + 1);
	pthread_mutex_unlock(&this->__buf_mutex);
	delete[] com;
	delete[] fx;
	delete[] fy;
	delete[] fz;
}

void	Client::SendMyInfo(void)
{
	char*	com = NULL;

	com = new char[100];
	com = strcpy(com, "/MY_INFO\n");
	com = strcat(com,DataNetwork::GetInstance()->FoundPlayer(this->fd)->GetPseudo());
	com = strcat(com, "\n/INFO_PLAYERS\n/INFO_GAMES\n/END\n");
	if (pthread_mutex_lock(&this->__buf_mutex) != 0)
	{
		std::cout << "error with mutex lockooo" << std::endl;
		return;
	}
	this->write_buf.AddStr(com, strlen(com) + 1);
	pthread_mutex_unlock(&this->__buf_mutex);
	delete[] com;
}

bool	Client::FillIp(const char* ip, const char* port)
{
	if (ip != 0)
	{
		struct addrinfo		hints;

		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		if (getaddrinfo(ip, port, &hints, &this->addr_info) == -1)
			return (false);
		this->addr = (sockaddr_in*)this->addr_info->ai_addr;
	}
	return (true);
}


int	Client::GetFd(void)
{
	return (this->fd);
}

char*	Client::GetPseudo(void)
{
	return (this->pseudo);
}



bool	Client::CreateData(void)
{
	char*		buf;
	DataNetwork*	data;
	DataPlayer*	player;
	int	i = 0;

	data = DataNetwork::GetInstance();
	player = data->FoundPlayer(this->fd);
	buf = this->read_buf.GetLine();
	while (buf != 0)
	{

		player->AddData(buf);
		if (strcmp(buf, "/END") == 0)
		{
			return (true);
		}
		buf = this->read_buf.GetLine();
		++i;
	}
	player->ShowData();
	return (false);
}

pthread_mutex_t*	Client::GetMutex(void)
{
	return (&this->__buf_mutex);
}
