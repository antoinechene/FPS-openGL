#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include <map>
#include "../uilibgp2015/OGL/ID_glibrary.h"


class	EventHandler : public ID::Singleton<EventHandler>
{
public:
	friend class ID::Singleton<EventHandler>;
	enum EVENT_TYPE
	{
		E_FORWARD = 0,
		E_BACKWARD,
		E_LEFT,
		E_RIGHT,
		E_JUMP,
		E_SHOT,
		E_ACTION,
		E_CHANGE_ANIM,
		E_PLAY_ANIM,
		E_NONE
	};
public:
	bool		Init(void);
	static void	KeyboardFunc(unsigned char, int, int);
	static void	KeyboardUpFunc(unsigned char, int, int);
	static void	MouseFunc(int, int, int, int);
	inline std::map<EVENT_TYPE, bool>*	GetCurrentEvents(void)
	{
		return (&this->__event_map);
	}
private:
		EventHandler(void);
	virtual ~EventHandler(void);
private:
	std::map<EVENT_TYPE, bool>	__event_map;
	std::map<char, EVENT_TYPE>	__key_bind;
	std::map<int, EVENT_TYPE>	__mouse_bind;
	ID::Event			__ev;
//	Wrapper_Event*		__we;

};

#endif

