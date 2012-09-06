#ifndef __PARSER_H__
#define __PARSER_H__

#include <map>
#include <list>
#include "../Tools/Buffer.h"

class	Client;

class DataPlayer;

class	Parser
{
public:
	enum RESPONSE
	{
		OK
	};
public:
		Parser(void);
		~Parser(void);
	bool	Init(void);
	bool	Parse(char*);
	bool	CompareTics(char*);
	Client*	GetClient(std::list<Client*>*, int);
	void	TransmitData(DataPlayer*, std::list<DataPlayer*>*, size_t);
	void	TransmitInfoPlayers(DataPlayer*, std::list<DataPlayer*>*);
	void	TransmitInfoGames(DataPlayer*);

	void	Server_CheckData(DataPlayer*, std::list<DataPlayer*>*);
	void	Client_CheckData(DataPlayer*);
	void	ShowData(DataPlayer*);
	void	ShowMessage(DataPlayer*, int);
	void	ShowMessageTo(DataPlayer*, int);
	void	TransmitDataToAll(DataPlayer*, size_t);
private:
	void	__SaveBuf(char*);
private:
	std::map<char*, bool (*)(std::list<RESPONSE>)>	cb_list;
	std::list<RESPONSE>				resp_list;
	Buffer						__buf;
};

#endif

