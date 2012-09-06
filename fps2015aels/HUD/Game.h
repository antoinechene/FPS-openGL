#ifndef Game_h
#define Game_h
//#include <iostream>
#include <list>

class Map;
class Player;
class Sounds;
class	Game
{
	public:
		Game(int id, Map* CurentMap, int Time, int Playermax);
		~Game();
		bool	EndGame();
		void	ActualizeTime();
		void	LoadMap(void);
		#include "GameInline.hpp"
	private:
		int			id;
		Map*			CurentMap;
		std::list<Player*>	PlayersList;
		int			TimeOfMap;
		int			NBPlayerMax;
	public:
		Sounds*			S;
};

#endif
