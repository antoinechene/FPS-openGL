#ifndef __DataNetwork_h__
#define __DataNetwork_h__


#include <list>
#include "Singleton.hpp"

class Client;
class DataGame;
class DataPlayer;

class	DataNetwork : public Singleton<DataNetwork>
{
	friend class	Singleton<DataNetwork>;

	public:
		DataNetwork();
		~DataNetwork();
		void			InitDataClient(Client*);
		void			AddGame(DataGame*);
		DataGame*		FoundGame(char*);
		DataGame*		FoundGame(int);
		DataPlayer*		FoundPlayer(int);
		Client*			FoundClient(int);
		void			SetClientsList(std::list<Client*>*);
		std::list<Client*>*	GetClientsList(void);
		std::list<DataGame*>*	GetGames(void);
	private:
		std::list<DataGame*>	__games;
		std::list<Client*>*	__clients;
};

#endif
