#include "Option_Menu.h"
#include "FirstMenu.h"
#include "../Objects/Display.h"
#include "../Sound/Sounds_mix.h"
#include "../game/Game.h"
#include "../Database/Player.h"

void	Callbackup(ID::Control* , ID::Event* , void* )
{
	Sounds*	sounds;

	sounds = Sounds::GetInstance();
	sounds->Volume_Music_Up();
//	sounds->Volume_Sounds_Up();
}

void	Callbackdown(ID::Control* , ID::Event* , void* )
{
	Sounds*	sounds;

	sounds = Sounds::GetInstance();
	sounds->Volume_Music_Down();
//	sounds->Volume_Sounds_Down();
}


void	CallbackBack(ID::Control* , ID::Event* , void* )
{
	Display*	disp;

	disp = Display::GetInstance();
	disp->menu[2]->Rem_Win();
	disp->menu[0]->AddWin();
//	disp->menu[]->Rem_Win();
//	((OptionMenu*)(disp->menu[0]))->Construct();
///	((FirstMenu*)(disp->menu[0]))->Construct();
}

void	CallbackValide(ID::Control* , ID::Event* , void* )
{
	Display*	disp;

	disp = Display::GetInstance();
	((OptionMenu*)(disp->menu[2]))->Get_Pseudo();

	disp->menu[0]->AddWin();
	(*(disp->game->GetPlayerList())->begin())->__pseudo = ((OptionMenu*)(disp->menu[2]))->Get_Pseudo();

//	disp->menu[]->Rem_Win();
//	((OptionMenu*)(disp->menu[0]))->Construct();
///	((FirstMenu*)(disp->menu[0]))->Construct();
}

OptionMenu::OptionMenu()
{
}

OptionMenu::~OptionMenu()
{
}

char*	OptionMenu::Get_Pseudo()
{
	return (this->pseudo->GetText());
}

void	OptionMenu::Construct()
{
	ID::Drawable*	Back;
//	ID::Surface*	back;
	ID::Drawable*	soundup;
	ID::Drawable*	sounddown;
	ID::Drawable*	valide;
	ID::Drawable*	quit;
//	ID::Label*	Play;
//	ID::Color	col(1.0f,0.0f,0.0f,1.0f);
//	ID::Label*	Option;
//	ID::Label*	Quit;

	Back = new ID::Drawable(800, 600);
	soundup = new ID::Drawable(40, 40);
	valide = new ID::Drawable(40, 40);
	this->pseudo = new ID::Textbox(215, 30, GLUT_BITMAP_9_BY_15);
	sounddown = new ID::Drawable(47, 20);
	quit = new ID::Drawable(140, 55);
//	sounddown->GetSurface()->LoadImage((char*)"../Resources/Pictures/-.tga");
	Back->GetSurface()->LoadImage((char*)"../Resources/Pictures/option.tga");
	soundup->SetPos(240, 180);
	this->pseudo->SetPos(260,220);
	sounddown->SetPos(170, 190);
	valide->SetPos(390, 180);
	quit->SetPos(55, 520);
	this->pseudo->GetSurface()->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	valide->GetSurface()->SetColor(0.0f, 1.0f, 1.0f, 1.0f);
	soundup->GetSurface()->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
	sounddown->GetSurface()->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
	quit->GetSurface()->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
	this->pseudo->GetSurface()->SetBlend(true);
	this->pseudo->SetText((char*)"Default");
	valide->GetSurface()->SetBlend(true);
	soundup->GetSurface()->SetBlend(true);
	sounddown->GetSurface()->SetBlend(true);
	quit->GetSurface()->SetBlend(true);
//	Play = new ID::Label((void*)GLUT_BITMAP_9_BY_15, "play", &col);
//	Option = new ID::Label((void*)GLUT_BITMAP_9_BY_15, "Options", &col);
//	Option->SetPos(0, 20);
//	Quit = new ID::Label((void*)GLUT_BITMAP_9_BY_15, "Quit", &col);
//	Quit->SetPos(0, 40);
	soundup->SetCbClickUp(&Callbackup, this);
	sounddown->SetCbClickUp(&Callbackdown, this);
	quit->SetCbClickUp(&CallbackBack, this);
	valide->SetCbClickUp(&CallbackValide, this);
	this->Add_Draw(Back);
	this->Add_Draw(soundup);
	this->Add_Draw(this->pseudo);
	this->Add_Draw(sounddown);
	this->Add_Draw(quit);
	this->Add_Draw(valide);
//	this->Add_Draw(Play);
//	this->Add_Draw(Option);
//	this->Add_Draw(Quit);
	this->Add_Win();
}

