#ifndef	__WRAPPER_INTERFACE_TEMPLATE_H__
#define	__WRAPPER_INTERFACE_TEMPLATE_H__

#ifndef	__MAKE_H
#include <pthread.h>
#endif
#include "../Common.h"

namespace	ID
{
	class	Surface;
	class	Wrapper_Interface_Template
	{
	public:
		virtual int		Init(void) = 0;
		virtual void		Destroy(void) = 0;
		virtual	int		CreateSurface(Surface* surface,
						      uint16_t width, uint16_t height,
						      uint32_t flags,
						      uint32_t rmask, uint32_t gmask,
						      uint32_t bmask, uint32_t amask) = 0;
		virtual int		SetVideoMode(Surface* surface,
						     uint16_t width, uint16_t height,
						     uint32_t flags) = 0;
		virtual void		DeleteSurface(Surface* surface) = 0;
		virtual uint32_t	GetPixel(Surface* surface, uint16_t x, uint16_t y) = 0;
		virtual void		SetPixel(Surface* surface,
						 uint16_t x, uint16_t y, uint32_t color) = 0;
		virtual int		FillRect(Surface* surface, Rect* rect,
						 uint32_t color) = 0;
		virtual int		BlitSurface(Surface* surface,
						    int, int) = 0;
	private:
		pthread_t	__id_thread;
	private:
		pthread_mutex_t	__mutex;
	};
};

#endif
