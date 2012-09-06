#include <string.h>
#include <iostream>
#include "DataPlayer.h"

DataPlayer::DataPlayer()
{
	this->__nickname = NULL;
}

DataPlayer::~DataPlayer()
{
	if (this->__nickname == NULL)
		return;
	delete[] this->__nickname;

}

void	DataPlayer::AddData(char* data)
{
	this->__data.push_back(data);
}

std::vector<char*>*	DataPlayer::GetData(void)
{
	return (&this->__data);
}

char*	DataPlayer::GetPseudo(void)
{
	return (this->__nickname);
}

void	DataPlayer::SetPseudo(char* pseudo)
{
	if (this->__nickname != NULL)
	{
		delete[] this->__nickname;
	}
	this->__nickname = new char[strlen(pseudo) + 1];
	strcpy(this->__nickname, pseudo);
}

void	DataPlayer::ClearData(void)
{
	size_t	i;

	i = 0;
	while (i < this->__data.size())
	{
		delete[] this->__data[i];
		++i;
	}
	this->__data.clear();
}

void	DataPlayer::SetFd(int fd)
{
	this->__fd = fd;
}

int	DataPlayer::GetFd(void)
{
	return (this->__fd);
}

void	DataPlayer::ShowData(void)
{
	size_t	i;

	i = 0;
	while (i < this->__data.size())
		++i;
}
