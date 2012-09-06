#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <unistd.h>

class	Buffer
{
public:
	Buffer(void);
	~Buffer(void);
	bool	NewBuffer(size_t);
	void	Init(size_t);
	ssize_t	ReadEntry(int, ssize_t);
	ssize_t	RecvEntry(int, ssize_t);
	size_t	GetSize(void);
	size_t	GetCapacity(void);
	size_t	GetRemainingSize(void);
	int	GetChar(char*);
	char	GetCharNoVerif(void);
	int	PeekChar(char*, size_t);
	char	PeekCharNoVerif(size_t);
	char*	GetLine(void);
	char*	PeekLine(size_t);
	char*	GetStr(size_t);
	char*	PeekStr(size_t, size_t);
	int	AddStr(const char*, size_t);
	void	Clear(void);
	char*	Flush(void);
	void	Print(void);
private:
	ssize_t	__CheckSize(ssize_t);
private:
	char*	buf;
	size_t	capacity;
	size_t	size;
	size_t	pos;
};

#endif

