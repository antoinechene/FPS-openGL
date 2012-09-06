#include "ID_Master_FCT.h"
#include "Keyboard_Manager.h"
#include <iostream>

#ifdef __SDL
#include "Wrapper/Wrapper_Event_SDL.h"
#include "Wrapper/Wrapper_Interface_SDL.h"
#endif

#ifdef __OGL
#include "Wrapper/Wrapper_Interface_OGL.h"
#endif

int	ID::Init(int flags)
{
	#ifdef __SDL
	if (SDL_Init(flags) == -1)
		return -1;
	#else
	(void)flags;
	#endif
	Keyboard_Manager::GetInstance();
	return 0;
}

/*
*	SDL require:
*	/!\ MUST ALWAYS BE CALLED AFTER THE SetVideoMode function /!\
*/
int	ID::InitWrappers()
{
	#ifdef __SDL
	if (ID::Wrapper_Event::GetInstance()->Init() == -1)
		return -1;
	#endif
	if (ID::Wrapper_Interface::GetInstance()->Init() == -1)
		return -1;
	return 0;
}

int	ID::DestroyWrappers()
{
	#ifdef __SDL
	ID::Wrapper_Event::GetInstance()->Destroy();
	ID::Wrapper_Event::GetInstance()->Kill();
	#endif
	ID::Wrapper_Interface::GetInstance()->Destroy();
	ID::Wrapper_Interface::GetInstance()->Kill();
	return 0;
}

void	ID::Quit()
{
	Keyboard_Manager::GetInstance()->Kill();
	#ifdef __SDL
	SDL_Quit();
	#endif
}

void	ID::About()
{
std::cout <<
"Isart Digital GPP Graphic Library\n\
v2012.03.15.0_ogl\n\
Copyright C 2012-Forever GPP Inc.\n\
All Right Reserved."
<< std::endl;
}
