#include "FirstMenu.h"
#include "ServerMenu.h"
#include "../Objects/Display.h"

void	CallbackNew(ID::Control* , ID::Event*, void*)
{
	Display*	disp;

	disp = Display::GetInstance();
	disp->menu[0]->Rem_Win();
	disp->menu[1]->AddWin();
//	((ServerMenu*)(disp->menu[1]))->Construct();
}

void	CallbackOption(ID::Control* , ID::Event*, void*)
{
	Display*	disp;

	disp = Display::GetInstance();
	disp->menu[0]->Rem_Win();
	disp->menu[2]->AddWin();
//	((ServerMenu*)(disp->menu[2]))->Construct();
//	disp->menu[0]->Rem_Win();
}

void	CallbackQuit(ID::Control*, ID::Event*, void*)
{
	Display*	disp;

	disp = Display::GetInstance();
	disp->menu[0]->Rem_Win();
	exit(0);
}


FirstMenu::FirstMenu()
{
}

FirstMenu::~FirstMenu()
{
}

void	FirstMenu::Construct()
{
	ID::Drawable*	Back;
	ID::Drawable*	newgame;
	ID::Drawable*	option;
	ID::Drawable*	quit;
//	ID::Label*	Play;
//	ID::Color	col(1.0f,0.0f,0.0f,1.0f);
//	ID::Label*	Option;
//	ID::Label*	Quit;

	Back = new ID::Drawable(800, 600);
	newgame = new ID::Drawable(415, 60);
	option = new ID::Drawable(280, 50);
	quit = new ID::Drawable(310, 60);
	Back->GetSurface()->LoadImage((char*)"../Resources/Pictures/menu_main.tga");
	newgame->SetPos(190, 190);
	option->SetPos(250, 285);
	quit->SetPos(245, 370);
	newgame->GetSurface()->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
	option->GetSurface()->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
	quit->GetSurface()->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
	newgame->GetSurface()->SetBlend(true);
	option->GetSurface()->SetBlend(true);
	quit->GetSurface()->SetBlend(true);
//	Play = new ID::Label((void*)GLUT_BITMAP_9_BY_15, "play", &col);
//	Option = new ID::Label((void*)GLUT_BITMAP_9_BY_15, "Options", &col);
//	Option->SetPos(0, 20);
//	Quit = new ID::Label((void*)GLUT_BITMAP_9_BY_15, "Quit", &col);
//	Quit->SetPos(0, 40);
	newgame->SetCbClickUp(&CallbackNew, this);
	option->SetCbClickUp(&CallbackOption, this);
	quit->SetCbClickUp(&CallbackQuit, this);
	this->Add_Draw(Back);
	this->Add_Draw(newgame);
	this->Add_Draw(option);
	this->Add_Draw(quit);
//	this->Add_Draw(Play);
//	this->Add_Draw(Option);
//	this->Add_Draw(Quit);
	this->Add_Win();
}

