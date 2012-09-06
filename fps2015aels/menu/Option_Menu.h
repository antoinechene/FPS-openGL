#ifndef __OPTION_MENU_H__
#define __OPTION_MENU_H__
#include "Menu.h"
#include "../uilibgp2015/OGL/ID_glibrary.h"

class OptionMenu : public Menu
{
	public:
		OptionMenu();
		~OptionMenu();
		virtual	void	Construct();
		char*	Get_Pseudo();
	private:
		ID::Textbox*	pseudo;
};

#endif

