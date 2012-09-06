#ifndef	__WRAPPER_EVENT_TEMPLATE_H__
#define	__WRAPPER_EVENT_TEMPLATE_H__

#ifndef	__MAKE_H
#include <pthread.h>
#endif
#include "../Event.h"

namespace	ID
{
	class	Wrapper_Event_Template
	{
	public:
		static void*	WrapEvent(void*);
		virtual int	Init(void) = 0;
		virtual void	Destroy(void) = 0;
		virtual int	WaitEvent(ID::Event* event) = 0;
		virtual int	PollEvent(ID::Event* event) = 0;
	private:
		pthread_t	__id_thread;
	private:
		pthread_mutex_t	__mutex;
	};
};

#endif
