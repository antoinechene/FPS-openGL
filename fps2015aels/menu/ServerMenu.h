#ifndef __SERVERMENU_H__
#define __SERVERMENU_H__

#include "Menu.h"
#include "../uilibgp2015/OGL/ID_glibrary.h"

class ServerMenu : public Menu
{
	public:
		ServerMenu();
		~ServerMenu();
		virtual	void	Construct();
		char*	Get_Text();
	private:
		ID::Textbox*	ip;
		ID::Textbox*	port;


};

#endif

