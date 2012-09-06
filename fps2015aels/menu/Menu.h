#ifndef __MENU_H__
#define __MENU_H__

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "../uilibgp2015/OGL/ID_glibrary.h"

class Menu
{
	public:
						Menu();
		virtual				~Menu();
		void				Add_Draw(ID::Drawable* d);
		std::vector<ID::Drawable*>*	Get_List();
		virtual	void			Construct();
		virtual void			Animate(int sens);
		void				Add_Win();
		void				AddWin();
		void				Rem_Win();
	protected:
		std::vector<ID::Drawable*>	list;
		std::vector<ID::Surface*>	surface;
};

#endif
