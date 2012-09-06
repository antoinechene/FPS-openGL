#include <new>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include "Buffer.h"

Buffer::Buffer(void)
{

}

Buffer::~Buffer(void)
{
	delete [] this->buf;
}

bool	Buffer::NewBuffer(size_t size)
{
	this->capacity = size;
	this->pos = 0;
	this->size = 0;
	try
	{
		this->buf = new char[this->capacity];
	}
	catch (std::bad_alloc&)
	{
		std::cout << "Error allocating memory" << std::endl;
		return (false);
	}
	return (true);
}

ssize_t	Buffer::__CheckSize(ssize_t nbread)
{
	if (this->capacity - this->size < (size_t)nbread)
	{
		if (this->pos != 0)
		{
			this->size = this->size - this->pos;
			memcpy(this->buf, this->buf + this->pos, this->size);
			this->pos = 0;
			if (this->capacity - this->size < (size_t)nbread)
				nbread = this->capacity - this->size;
		}
		else
			nbread = this->capacity - this->size;
	}
	return (nbread);
}

ssize_t	Buffer::ReadEntry(int fd, ssize_t nbread)
{
	ssize_t nb;

	nbread = this->__CheckSize(nbread);
	nb = -1;
	if (nbread > 0)
	{
		nb = read(fd, this->buf + this->size, nbread);
		if (nb > 0)
			this->size = this->size + nb;
	}
	return (nb);
}

ssize_t	Buffer::RecvEntry(int fd, ssize_t nbread)
{
	ssize_t nb;

	nbread = this->__CheckSize(nbread);
	if (nbread > 0)
	{
		nb = recv(fd, this->buf + this->size, nbread, 0);
		if (nb > 0)
		{
			this->size = nb;
			return (nb);
		}
	}
	return (0);
}

size_t	Buffer::GetSize(void)
{
	return (this->size);
}

size_t	Buffer::GetCapacity(void)
{
	return (this->capacity);
}

size_t	Buffer::GetRemainingSize(void)
{
	return (this->pos + this->capacity - this->size);
}

int	Buffer::GetChar(char* c)
{
	if (this->size == 0)
		return (-1);
	else
	{
		*c = *(this->buf + this->pos);
		this->pos = this->pos + 1;
		if (this->pos == this->size)
		{
			this->pos = 0;
			this->size = 0;
		}
		return (0);
	}
}

char	Buffer::GetCharNoVerif(void)
{
	char	c;

	if (this->size == 0)
		return (0);
	else
	{
		c = *(this->buf + this->pos);
		this->pos = this->pos + 1;
		if (this->pos == this->size)
		{
			this->pos = 0;
			this->size = 0;
		}
		return (c);
	}
}

int	Buffer::PeekChar(char* c, size_t pos)
{
	if (pos > this->size)
		return (-1);
	else
	{
		*c = *(this->buf + pos);
		return (0);
	}
}

char	Buffer::PeekCharNoVerif(size_t pos)
{
	if (pos > this->size)
		return (0);
	else
		return (*(this->buf + pos));
}

char*	Buffer::GetLine(void)
{
	char*	str;
	int	i;

	i = 0;
	while (this->pos + i < this->size && *(this->buf + this->pos + i) != '\n')
		i = i + 1;
	if (i == 0 || *(this->buf + this->pos + i) != '\n')
		return (NULL);
	str = new (std::nothrow) char[i + 1];
	if (str == NULL)
		return (NULL);
	memcpy(str, this->buf + this->pos, i);
	*(str + i) = '\0';
	this->pos = this->pos + i + 1;
	if (this->pos == this->size)
	{
		this->pos = 0;
		this->size = 0;
	}
	return (str);
}

char*	Buffer::PeekLine(size_t pos_start)
{
	char*	str;
	int	i;

	i = 0;
	while (this->pos + i + pos_start <= this->size &&
	       *(this->buf + this->pos + i) != '\n')
		i = i + 1;
	if (this->pos + i + pos_start > this->size ||
	    *(this->buf + this->pos + i) != '\n')
		return (NULL);
	str = new (std::nothrow) char[i + 1];
	if (str == NULL)
		return (NULL);
	memcpy(str, this->buf + this->pos + pos_start, i);
	*(str + i) = '\0';
	return (str);
}

char*	Buffer::GetStr(size_t size)
{
	char*	str;

	if (this->pos + size > this->size)
		return (NULL);
	str = new (std::nothrow) char[size + 1];
	if (str == NULL)
		return (NULL);
	memcpy(str, this->buf + this->pos, size);
	*(str + size + 1) = '\0';
	this->pos = this->pos + size;
	if (this->pos == this->size)
	{
		this->pos = 0;
		this->size = 0;
	}
	return (str);
}

char*	Buffer::PeekStr(size_t start, size_t size)
{
	char*	str;

	if (start + size > this->size)
		return (NULL);
	str = new (std::nothrow) char[size + 1];
	if (str == NULL)
		return (NULL);
	memcpy(str, this->buf + this->pos + start, size);
	*(str + size + 1) = '\0';
	return (str);

}

int	Buffer::AddStr(const char* str, size_t size)
{
	if (this->size + size > this->capacity)
		return (1);
	memcpy(this->buf + this->size, str, size);
	this->size = this->size + size;
	return (0);
}

void	Buffer::Clear(void)
{
	this->pos = 0;
	this->size = 0;
}

char*	Buffer::Flush(void)
{
	char*	str;

	str = new (std::nothrow) char[this->size + 1];
	if (str == NULL)
		return (NULL);
	memcpy(str, this->buf + this->pos, this->size);
	*(str + this->size + 1) = '\0';
	this->pos = 0;
	this->size = 0;
	return (str);
}

void	Buffer::Print(void)
{
	size_t	i;

	i = this->pos;
	while (i != this->capacity)
	{
		write(1, this->buf + this->pos + i, 1);
		i = i + 1;
	}
}


