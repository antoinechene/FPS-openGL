#include "ServerMenu.h"
#include "FirstMenu.h"
#include "../Objects/Display.h"
#include "../NetworkHandler/Network.h"
#include "../NetworkHandler/Client.h"
#include "../game/Game.h"
#include "../HUD/Hud.h"
#include "../Database/Player.h"

void	CallbackBack(ID::Control* sender, ID::Event*, void*);
/*void	CallbackNew(ID::Control* sender, ID::Event* ev, void* data)
{
	std::cout<<"new"<<std::endl;
	std::cout<<sender<<std::endl;
}
*/
void	CallbackBack2(ID::Control* , ID::Event*, void*)
{
	Display*	disp;

	disp = Display::GetInstance();
	disp->menu[1]->Rem_Win();
	disp->menu[0]->AddWin();
}

void	Callbackvalide(ID::Control*, ID::Event*, void*)
{
	Display*	disp;

	disp = Display::GetInstance();
	((ServerMenu*)(disp->menu[1]))->Get_Text();
}



ServerMenu::ServerMenu()
{
}

ServerMenu::~ServerMenu()
{
}

char*	ServerMenu::Get_Text()
{
	Network*	net;
	Client*		cli;

	net = new Network(); 
	cli = new Client();
	
//	cli->pseudo = (*Display::GetInstance()->game->GetPlayerList()->begin())->__pseudo;
	cli->NewConnection(this->ip->GetText(), this->port->GetText(), net);
	Display::GetInstance()->game->LoadMap();
	Display::GetInstance()->InGame = true;
	Display::GetInstance()->hud->Init_All((*Display::GetInstance()->game->GetPlayerList()->begin()), Display::GetInstance()->game);

	Display::GetInstance()->menu[1]->Rem_Win();

	return (this->ip->GetText());
}

void	ServerMenu::Construct()
{
	ID::Drawable*	Back;
//	ID::Textbox*	newgame;
	ID::Drawable*	valide;
	ID::Drawable*	_back;
//	ID::Label*	Play;
//	ID::Color	col(1.0f,0.0f,0.0f,1.0f);
//	ID::Label*	Option;

	Back = new ID::Drawable(800, 600);
	this->ip = new ID::Textbox(215, 30, GLUT_BITMAP_9_BY_15);
	this->port = new ID::Textbox(50, 30, GLUT_BITMAP_9_BY_15);
	valide = new ID::Drawable(80, 30);
	_back = new ID::Drawable(310, 60);
	Back->GetSurface()->LoadImage((char*)"../Resources/Pictures/server.tga");
	this->ip->SetPos(260, 220);
	this->port->SetPos(480, 220);

	valide->SetPos(550, 220);
	_back->SetPos(45, 470);
	this->ip->GetSurface()->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	this->port->GetSurface()->SetColor(1.0f, 1.0f, 1.0f, 1.0f);


	valide->GetSurface()->SetColor(0.0f, 1.0f, 0.0f, 0.5f);
	_back->GetSurface()->SetColor(1.0f, 0.0f, 0.0f, 0.7f);
	this->ip->GetSurface()->SetBlend(true);
	this->port->GetSurface()->SetBlend(true);

	valide->GetSurface()->SetBlend(true);
	_back->GetSurface()->SetBlend(true);
//	Play = new ID::Label((void*)GLUT_BITMAP_9_BY_15, "play", &col);
//	Option = new ID::Label((void*)GLUT_BITMAP_9_BY_15, "Options", &col);
//	Option->SetPos(0, 20);
//	Quit = new ID::Label((void*)GLUT_BITMAP_9_BY_15, "Quit", &col);
//	Quit->SetPos(0, 40);
//	newgame->SetCbClickUp(&CallbackNew, this);
	valide->SetCbClickUp(&Callbackvalide, this);
	_back->SetCbClickUp(&CallbackBack2, this);
	this->Add_Draw(Back);
	this->Add_Draw(this->ip);
	this->Add_Draw(valide);
	this->Add_Draw(_back);
	this->Add_Draw(this->port);

//	this->Add_Draw(Play);
//	this->Add_Draw(Option);
//	this->Add_Draw(Quit);
	this->Add_Win();
}

