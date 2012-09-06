#include "ID_Master_FCT.h"
#include "Draw_Geometry/Draw_Geometry_Rect.h"
#include "Draw_Geometry/Draw_Geometry_Line.h"
#include "Draw_Geometry/Draw_Geometry_Circle.h"
#include "Draw_Geometry/Draw_Geometry_Polygon.h"
#include "Font.h"
#include "Keyboard_Manager.h"
#include <iostream>

#ifdef __SDL
#include "Wrapper/Wrapper_Event_SDL.h"
#include "Wrapper/Wrapper_Interface_SDL.h"
#endif

int	ID::Init(int flags)
{
	#ifdef __SDL
	if (SDL_Init(flags) == -1)
		return -1;
	#else
	(void)flags;
	#endif
	if (TTF_Init() == -1)
		return -1;
	Font::GetInstance();
	Keyboard_Manager::GetInstance();
	Draw_Geometry_Rect::GetInstance();
	Draw_Geometry_Line::GetInstance();
	ID::Draw_Geometry_Circle::GetInstance();
	Draw_Geometry_Polygon::GetInstance();
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
	if (ID::Wrapper_Interface::GetInstance()->Init() == -1)
		return -1;
	#endif
	return 0;
}

int	ID::DestroyWrappers()
{
	#ifdef __SDL
	ID::Wrapper_Event::GetInstance()->Destroy();
	ID::Wrapper_Interface::GetInstance()->Destroy();
	ID::Wrapper_Event::GetInstance()->Kill();
	ID::Wrapper_Interface::GetInstance()->Kill();
	#endif
	return 0;
}

void	ID::Quit()
{
	Draw_Geometry_Rect::GetInstance()->Kill();
	Draw_Geometry_Line::GetInstance()->Kill();
	Draw_Geometry_Circle::GetInstance()->Kill();
	Draw_Geometry_Polygon::GetInstance()->Kill();
	Font::GetInstance()->Kill();
	Keyboard_Manager::GetInstance()->Kill();
	TTF_Quit();
	#ifdef __SDL
	SDL_Quit();
	#endif
}

void	ID::About()
{
std::cout <<
"Isart Digital GPP Graphic Library\n\
v2012.01.14.18\n\
Copyright C 2011-Forever GPP Inc.\n\
All Right Reserved."
<< std::endl;
}
