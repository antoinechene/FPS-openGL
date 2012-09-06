#ifndef __DataPlayer_h__
#define __DataPlayer_h__

#include <vector>

class	DataPlayer
{
public:
	DataPlayer();
	~DataPlayer();
	void			AddData(char*);
	int			GetFd(void);
	void			SetFd(int);
	char*			GetPseudo(void);
	void			SetPseudo(char*);
	void			ClearData(void);
	std::vector<char*>*	GetData(void);
	void			ShowData(void);
private:
	int			__fd;
	char*			__nickname;
	std::vector<char*>	__data;
};

#endif
