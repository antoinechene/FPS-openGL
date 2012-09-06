#ifndef	__WRAPPER_EVENT_OGL_H__
#define	__WRAPPER_EVENT_OGL_H__

#ifndef	__MAKE_H
#include <pthread.h>
#include <list>
#include <sys/time.h>
#endif

#include "Wrapper_Event_Template.h"
#include "../Event.h"
#include "../Singleton.hpp"

namespace	ID
{
	class	Control;
	class	Wrapper_Event : public Wrapper_Event_Template,
				public Singleton<ID::Wrapper_Event>
	{
			friend class	Singleton<ID::Wrapper_Event>;

		public:
			static void*	WrapEvent(void*);
			int		Init(void);
			void		Destroy(void);
			int		WaitEvent(Event* event);
			int		PollEvent(Event* event);
			int		PushEvent(Event* event);
			void		AddKeyUpControl(Control* control);
			void		AddKeyDownControl(Control* control);
			void		DelKeyUpControl(Control* control);
			void		DelKeyDownControl(Control* control);
			void		ApplyKeyUp(ID::Event* e);
			void		ApplyKeyDown(ID::Event* e);
			void		SetIntervalClick(unsigned int ms);
			void		SetIntervalDblClick(unsigned int ms);
			bool		CheckIntervalClick(struct timeval* a, struct timeval* b);
			bool		CheckIntervalDblClick(struct timeval* a, struct timeval* b);
		private:
			Wrapper_Event(void);
			~Wrapper_Event(void);

		private:
			pthread_t		__id_thread;
			bool			__alive;
			pthread_mutex_t		__mutex;
			Event*			__events_queue;
			int			__events_size;
			std::list<Control*>	__keyDownControl;
			std::list<Control*>	__keyUpControl;
			struct timeval		__intervalClick;
			struct timeval		__intervalDblClick;
	};
};

#endif

