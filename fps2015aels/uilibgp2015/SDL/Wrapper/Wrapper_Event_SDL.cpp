#include "Wrapper_Event_SDL.h"
#include <SDL/SDL.h>
#include <unistd.h>
#include <iostream>
#include "../Constantes.h"
#include "../Control/Control.h"

ID::Wrapper_Event::Wrapper_Event(void) : __alive(true)
{
	this->__intervalClick.tv_sec = DEFAULT_INTERVAl_CLICK_SEC;
	this->__intervalClick.tv_usec = DEFAULT_INTERVAl_CLICK_uSEC;
	this->__intervalDblClick.tv_sec = DEFAULT_INTERVAl_DBLCLICK_SEC;
	this->__intervalDblClick.tv_usec = DEFAULT_INTERVAl_DBLCLICK_uSEC;
}

ID::Wrapper_Event::~Wrapper_Event(void)
{
/*	std::list<ID::Event*>::iterator	it;

	it = this->__events_queue.begin();
	while (it != this->__events_queue.end())
	{
		delete *it;
		++it;
	}*/
	delete[] this->__events_queue;
}

int	ID::Wrapper_Event::Init(void)
{
	this->__events_size = 0;
//	this->__events_queue = new ID::Event[400];
	if (pthread_mutex_init(&(this->__mutex), NULL) != 0)
		return -1;
//	pthread_create(&(this->__id_thread), NULL, this->WrapEvent, this);
	return 0;
}

void	ID::Wrapper_Event::Destroy(void)
{
	this->__alive = false;
/*	if (pthread_join(this->__id_thread, NULL) != 0)
	{
		std::cout << "Error pthread_join Wrapper_Event" << std::endl;
	}*/
}
/*
void*	ID::Wrapper_Event::WrapEvent(void* _we)
{
	SDL_Event		event;
	ID::Event*		id_event;
	ID::Wrapper_Event*	we;

	id_event = new ID::Event;
	we = (ID::Wrapper_Event*)_we;
	while (we->__alive == true)
	{
		if (SDL_PollEvent(&event) == 1 &&
		    we->__events_size < 400)
//		    we->__events_queue.size() < 400)
		{
	//		id_event = new ID::Event;
	//		if (id_event == NULL)
	//			continue ;
			id_event->type = 0;
			if (event.type == SDL_MOUSEMOTION)
			{
				id_event->type = EVENT_MOTION;
				id_event->motion.type = EVENT_MOTION;
				id_event->motion.state = event.motion.state;
				id_event->motion.x = event.motion.x;
				id_event->motion.y = event.motion.y;
				id_event->motion.x_rel = event.motion.xrel;
				id_event->motion.y_rel = event.motion.yrel;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				id_event->type = EVENT_KEY_DOWN;
				id_event->keyDown.type = EVENT_KEY_DOWN;
				id_event->keyDown.keysym.scancode = event.key.keysym.scancode;
				id_event->keyDown.keysym.sym = (ID::Key)event.key.keysym.sym;
				id_event->keyDown.keysym.mod = (ID::Mod)event.key.keysym.mod;
			}
			else if (event.type == SDL_KEYUP)
			{
				id_event->type = EVENT_KEY_UP;
				id_event->keyUp.type = EVENT_KEY_UP;
				id_event->keyUp.keysym.scancode = event.key.keysym.scancode;
				id_event->keyUp.keysym.sym = (ID::Key)event.key.keysym.sym;
				id_event->keyUp.keysym.mod = (ID::Mod)event.key.keysym.mod;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				id_event->type = EVENT_CLICK_DOWN;
				id_event->clickDown.type = EVENT_CLICK_DOWN;
				if (event.button.button == SDL_BUTTON_LEFT)
					id_event->clickDown.button = ID::BUTTON_LEFT;
				else if (event.button.button == SDL_BUTTON_MIDDLE)
					id_event->clickDown.button = ID::BUTTON_MID;
				else if (event.button.button == SDL_BUTTON_RIGHT)
					id_event->clickDown.button = ID::BUTTON_RIGHT;
				id_event->clickDown.x = event.button.x;
				id_event->clickDown.y = event.button.y;
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				id_event->type = EVENT_CLICK_UP;
				id_event->clickUp.type = EVENT_CLICK_UP;
				if (event.button.button == SDL_BUTTON_LEFT)
					id_event->clickUp.button = ID::BUTTON_LEFT;
				else if (event.button.button == SDL_BUTTON_MIDDLE)
					id_event->clickUp.button = ID::BUTTON_MID;
				else if (event.button.button == SDL_BUTTON_RIGHT)
					id_event->clickUp.button = ID::BUTTON_RIGHT;
				id_event->clickUp.x = event.button.x;
				id_event->clickUp.y = event.button.y;
			}
			else if (event.type == SDL_VIDEORESIZE)
			{
				id_event->type = EVENT_RESIZE;
				id_event->resize.type = EVENT_RESIZE;
				id_event->resize.w = event.resize.w;
				id_event->resize.h = event.resize.h;
			}
			else if (event.type == SDL_QUIT)
			{
				id_event->type = EVENT_QUIT;
				id_event->quit.type = EVENT_QUIT;
			}
			if (id_event->type != 0)
			{
				we->__events_queue[we->__events_size] = *id_event;
				++(we->__events_size);
			}
		//		we->__events_queue.push_back(id_event);
		//	else
		//		delete id_event;
		}
		usleep(500);
	}
	delete id_event;
	return NULL;
}
*/
int	ID::Wrapper_Event::WaitEvent(ID::Event* e)
{
	SDL_Event	event;

	if (SDL_WaitEvent(&event) == 1)
	{
		if (event.type == SDL_MOUSEMOTION)
		{
			e->type = ID::EVENT_MOTION;
			e->motion.state = event.motion.state;
			e->motion.x = event.motion.x;
			e->motion.y = event.motion.y;
			e->motion.x_rel = event.motion.xrel;
			e->motion.y_rel = event.motion.yrel;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			e->type = ID::EVENT_CLICK_DOWN;
			if (event.button.button == SDL_BUTTON_LEFT)
				e->clickDown.button = ID::BUTTON_LEFT;
			else if (event.button.button == SDL_BUTTON_MIDDLE)
				e->clickDown.button = ID::BUTTON_MID;
			else if (event.button.button == SDL_BUTTON_RIGHT)
				e->clickDown.button = ID::BUTTON_RIGHT;
			e->clickDown.x = event.button.x;
			e->clickDown.y = event.button.y;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			e->type = ID::EVENT_CLICK_UP;
			if (event.button.button == SDL_BUTTON_LEFT)
				e->clickUp.button = ID::BUTTON_LEFT;
			else if (event.button.button == SDL_BUTTON_MIDDLE)
				e->clickUp.button = ID::BUTTON_MID;
			else if (event.button.button == SDL_BUTTON_RIGHT)
				e->clickUp.button = ID::BUTTON_RIGHT;
			e->clickUp.x = event.button.x;
			e->clickUp.y = event.button.y;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			e->type = ID::EVENT_KEY_DOWN;
			e->keyDown.keysym.scancode = event.key.keysym.scancode;
			e->keyDown.keysym.sym = (ID::Key)event.key.keysym.sym;
			e->keyDown.keysym.mod = (ID::Mod)event.key.keysym.mod;
		}
		else if (event.type == SDL_KEYUP)
		{
			e->type = ID::EVENT_KEY_UP;
			e->keyUp.keysym.scancode = event.key.keysym.scancode;
			e->keyUp.keysym.sym = (ID::Key)event.key.keysym.sym;
			e->keyUp.keysym.mod = (ID::Mod)event.key.keysym.mod;
		}
		else if (event.type == SDL_VIDEORESIZE)
		{
			e->type = ID::EVENT_RESIZE;
			e->resize.w = event.resize.w;
			e->resize.h = event.resize.h;
		}
		else if (event.type == SDL_QUIT)
		{
			e->type = ID::EVENT_QUIT;
		}
		return 1;
	}
	return 0;
}

int	ID::Wrapper_Event::PollEvent(ID::Event* e)
{
	SDL_Event	event;

	if (SDL_PollEvent(&event) == 1)
	{
		e->type = 0;
		if (event.type == SDL_MOUSEMOTION)
		{
			e->type = ID::EVENT_MOTION;
			e->motion.state = event.motion.state;
			e->motion.x = event.motion.x;
			e->motion.y = event.motion.y;
			e->motion.x_rel = event.motion.xrel;
			e->motion.y_rel = event.motion.yrel;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			e->type = ID::EVENT_CLICK_DOWN;
			if (event.button.button == SDL_BUTTON_LEFT)
				e->clickDown.button = ID::BUTTON_LEFT;
			else if (event.button.button == SDL_BUTTON_MIDDLE)
				e->clickDown.button = ID::BUTTON_MID;
			else if (event.button.button == SDL_BUTTON_RIGHT)
				e->clickDown.button = ID::BUTTON_RIGHT;
			e->clickDown.x = event.button.x;
			e->clickDown.y = event.button.y;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			e->type = ID::EVENT_CLICK_UP;
			if (event.button.button == SDL_BUTTON_LEFT)
				e->clickUp.button = ID::BUTTON_LEFT;
			else if (event.button.button == SDL_BUTTON_MIDDLE)
				e->clickUp.button = ID::BUTTON_MID;
			else if (event.button.button == SDL_BUTTON_RIGHT)
				e->clickUp.button = ID::BUTTON_RIGHT;
			e->clickUp.x = event.button.x;
			e->clickUp.y = event.button.y;
		}
		else if (event.type == ID::EVENT_CLICK)
		{
			e->type = ID::EVENT_CLICK;
			if (event.button.button == SDL_BUTTON_LEFT)
				e->click.button = ID::BUTTON_LEFT;
			else if (event.button.button == SDL_BUTTON_MIDDLE)
				e->click.button = ID::BUTTON_MID;
			else if (event.button.button == SDL_BUTTON_RIGHT)
				e->click.button = ID::BUTTON_RIGHT;
			e->click.x = event.button.x;
			e->click.y = event.button.y;
		}
		else if (event.type == ID::EVENT_DOUBLE_CLICK)
		{
			e->type = ID::EVENT_DOUBLE_CLICK;
			if (event.button.button == SDL_BUTTON_LEFT)
				e->doubleClick.button = ID::BUTTON_LEFT;
			else if (event.button.button == SDL_BUTTON_MIDDLE)
				e->doubleClick.button = ID::BUTTON_MID;
			else if (event.button.button == SDL_BUTTON_RIGHT)
				e->doubleClick.button = ID::BUTTON_RIGHT;
			e->doubleClick.x = event.button.x;
			e->doubleClick.y = event.button.y;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			e->type = ID::EVENT_KEY_DOWN;
			e->keyDown.keysym.scancode = event.key.keysym.scancode;
			e->keyDown.keysym.sym = (ID::Key)event.key.keysym.sym;
			e->keyDown.keysym.mod = (ID::Mod)event.key.keysym.mod;
		}
		else if (event.type == SDL_KEYUP)
		{
			e->type = ID::EVENT_KEY_UP;
			e->keyUp.keysym.scancode = event.key.keysym.scancode;
			e->keyUp.keysym.sym = (ID::Key)event.key.keysym.sym;
			e->keyUp.keysym.mod = (ID::Mod)event.key.keysym.mod;
		}
		else if (event.type == SDL_VIDEORESIZE)
		{
			e->type = ID::EVENT_RESIZE;
			e->resize.w = event.resize.w;
			e->resize.h = event.resize.h;
		}
		else if (event.type == SDL_QUIT)
		{
			e->type = ID::EVENT_QUIT;
		}
		return 1;
	}
	return 0;
}

int	ID::Wrapper_Event::PushEvent(Event* event)
{
	SDL_Event	SDL_e;

	if (event->type == ID::EVENT_MOTION)
	{
		SDL_e.type = SDL_MOUSEMOTION;
		SDL_e.motion.state = event->motion.state;
		SDL_e.motion.x = event->motion.x;
		SDL_e.motion.y = event->motion.y;
		SDL_e.motion.xrel = event->motion.x_rel;
		SDL_e.motion.yrel = event->motion.y_rel;
	}
	else if (event->type == ID::EVENT_CLICK_DOWN)
	{
		SDL_e.type = SDL_MOUSEBUTTONDOWN;
		SDL_e.button.button = (Uint8)event->clickDown.button;
		SDL_e.button.state = SDL_PRESSED;
		SDL_e.button.x = event->clickDown.x;
		SDL_e.button.y = event->clickDown.y;
	}
	else if (event->type == ID::EVENT_CLICK_UP)
	{
		SDL_e.type = SDL_MOUSEBUTTONUP;
		SDL_e.button.button = (Uint8)event->clickUp.button;
		SDL_e.button.state = SDL_RELEASED;
		SDL_e.button.x = event->clickUp.x;
		SDL_e.button.y = event->clickUp.y;
	}
	else if (event->type == ID::EVENT_CLICK)
	{
		SDL_e.type = ID::EVENT_CLICK;
		SDL_e.button.button = (Uint8)event->click.button;
		SDL_e.button.state = SDL_RELEASED;
		SDL_e.button.x = event->click.x;
		SDL_e.button.y = event->click.y;
	}
	else if (event->type == ID::EVENT_DOUBLE_CLICK)
	{
		SDL_e.type = ID::EVENT_DOUBLE_CLICK;
		SDL_e.button.button = (Uint8)event->doubleClick.button;
		SDL_e.button.state = SDL_RELEASED;
		SDL_e.button.x = event->doubleClick.x;
		SDL_e.button.y = event->doubleClick.y;
	}
	else if (event->type == ID::EVENT_KEY_DOWN)
	{
		SDL_e.type = SDL_KEYDOWN;
		SDL_e.key.state = SDL_PRESSED;
		SDL_e.key.keysym.scancode = event->keyDown.keysym.scancode;
		SDL_e.key.keysym.sym = (SDLKey)event->keyDown.keysym.sym;
		SDL_e.key.keysym.mod = (SDLMod)event->keyDown.keysym.mod;
	}
	else if (event->type == ID::EVENT_KEY_UP)
	{
		SDL_e.type = SDL_KEYUP;
		SDL_e.key.state = SDL_RELEASED;
		SDL_e.key.keysym.scancode = event->keyUp.keysym.scancode;
		SDL_e.key.keysym.sym = (SDLKey)event->keyUp.keysym.sym;
		SDL_e.key.keysym.mod = (SDLMod)event->keyUp.keysym.mod;
	}
	else if (event->type == EVENT_RESIZE)
	{
		SDL_e.type = SDL_VIDEORESIZE;
		SDL_e.resize.w = event->resize.w;
		SDL_e.resize.h = event->resize.h;
	}
	else if (event->type == EVENT_QUIT)
	{
		SDL_e.type = SDL_QUIT;
	}
	return SDL_PushEvent(&SDL_e);
}

void	ID::Wrapper_Event::AddKeyUpControl(Control* c)
{
	this->__keyUpControl.push_back(c);
}

void	ID::Wrapper_Event::AddKeyDownControl(Control* c)
{
	this->__keyDownControl.push_back(c);
}

void	ID::Wrapper_Event::DelKeyUpControl(Control* c)
{
	std::list<Control*>::iterator	it;
	std::list<Control*>::iterator	end;

	it = this->__keyUpControl.begin();
	end = this->__keyUpControl.end();
	while (it != end)
	{
		if (*it == c)
		{
			this->__keyUpControl.erase(it);
			return ;
		}
		++it;
	}
}

void	ID::Wrapper_Event::DelKeyDownControl(Control* c)
{
	std::list<Control*>::iterator	it;
	std::list<Control*>::iterator	end;

	it = this->__keyDownControl.begin();
	end = this->__keyDownControl.end();
	while (it != end)
	{
		if (*it == c)
		{
			this->__keyDownControl.erase(it);
			return ;
		}
		++it;
	}
}

void	ID::Wrapper_Event::ApplyKeyUp(ID::Event* e)
{
	std::list<Control*>::iterator	it;
	std::list<Control*>::iterator	end;

	it = this->__keyUpControl.begin();
	end = this->__keyUpControl.end();
	while (it != end)
	{
		(*it)->KeyUp(e);
		++it;
	}
}

void	ID::Wrapper_Event::ApplyKeyDown(ID::Event* e)
{
	std::list<Control*>::iterator	it;
	std::list<Control*>::iterator	end;

	it = this->__keyDownControl.begin();
	end = this->__keyDownControl.end();
	while (it != end)
	{
		(*it)->KeyDown(e);
		++it;
	}
}

void	ID::Wrapper_Event::SetIntervalClick(unsigned int ms)
{
	this->__intervalClick.tv_sec = ms / 1000;
	this->__intervalClick.tv_usec = ms * 1000;
}

void	ID::Wrapper_Event::SetIntervalDblClick(unsigned int ms)
{
	this->__intervalDblClick.tv_sec = ms / 1000;
	this->__intervalDblClick.tv_usec = ms * 1000;
}

bool	ID::Wrapper_Event::CheckIntervalClick(struct timeval* a, struct timeval* b)
{
	int		s;
	int		us;

	s = b->tv_sec - a->tv_sec;
	if (s < 0)
		s = -s;
	us = b->tv_usec - a->tv_usec;
	if (us < 0)
	{
		--s;
		us += 1000000;
	}
	if (s > this->__intervalClick.tv_sec ||
	    us > this->__intervalClick.tv_usec)
		return false;
	return true;
}

bool	ID::Wrapper_Event::CheckIntervalDblClick(struct timeval* a, struct timeval* b)
{
	int		s;
	int		us;

	s = b->tv_sec - a->tv_sec;
	if (s < 0)
		s = -s;
	us = b->tv_usec - a->tv_usec;
	if (us < 0)
	{
		--s;
		us += 1000000;
	}
	if (s > this->__intervalDblClick.tv_sec ||
	    us > this->__intervalDblClick.tv_usec)
		return false;
	return true;
}

