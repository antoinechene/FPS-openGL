#ifndef	__WRAPPER_INTERFACE_SDL_H__
#define	__WRAPPER_INTERFACE_SDL_H__

#ifdef	__SDL

#ifndef	__MAKE_H
#include <pthread.h>
#include <vector>
#include <SDL/SDL.h>
#endif

#include "Wrapper_Interface_Template.h"
#include "../Singleton.hpp"
#include "../Surface.h"

namespace	ID
{
	class	Wrapper_Interface : public Wrapper_Interface_Template,
				    public Singleton<ID::Wrapper_Interface>
	{
		friend class	Singleton<ID::Wrapper_Interface>;
	public:
		typedef	SDL_Surface	wrapper_surface;
		#include "Wrapper_Interface_SDL_inline.hpp"
	private:
		Wrapper_Interface(void);
		~Wrapper_Interface(void);
	};
};

#endif
#endif
