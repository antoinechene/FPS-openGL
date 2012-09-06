#ifndef __ID_MASTER_FCT_H__
#define __ID_MASTER_FCT_H__

#ifdef	__SDL
#ifndef	__MAKE_H
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#endif
#endif

namespace	ID
{
	int	Init(int flags);
	int	InitWrappers(void);
	int	DestroyWrappers();
	void	Quit(void);
	void	About(void);
};

#endif
