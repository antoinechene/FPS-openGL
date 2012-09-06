#ifndef __DataGame_h__
#define __DataGame_h__

#include <list>
#include "DataPlayer.h"

class	DataGame
{
public:
	DataGame();
	~DataGame();
	void	AddPlayer(DataPlayer*);
	void	SetID(char*);
	char*	GetID(void);
	std::list<DataPlayer*>*	GetPlayers(void);
private:
	char*			__ID;
	std::list<DataPlayer*>	__players;

};

#endif
