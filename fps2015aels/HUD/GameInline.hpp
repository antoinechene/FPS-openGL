#ifndef GameInline_hpp
#define GameInline_hpp

inline int	GetID(void)
{
	return (this->id);
}

inline void	SetID(int id)
{
	this->id = id;
}

inline Map*	GetCurrentMap(void)
{
	return (this->CurentMap);
}

inline void	SetCurrentMap(Map* m)
{
	this->CurentMap = m;
}

inline std::list<Player*>*	GetPlayerList(void)
{
	return (&this->PlayersList);
}

inline void	AddPlayer(Player* p)
{
	this->PlayersList.push_back(p);
}

inline void	RemovePlayer(Player* p)
{
	this->PlayersList.remove(p);
}


inline int	GetTime(void)
{
	return (this->TimeOfMap);
}

inline void	SetTime(int t)
{
	this->TimeOfMap = t;
}

inline int	GetNBPlayerMax(void)
{
	return (this->NBPlayerMax);
}

inline void	SetNBPlayerMax(int nb)
{
	this->NBPlayerMax = nb;
}

#endif
