#include <GL/glut.h>
//#include "../Objects/FBXLoader.h"
#include "Game.h"
#include "Hud.h"
//#include "../Objects/Display.h"
//#include "../map/Map.h"
//#include "../Objects/Ball.h"
//#include "../Objects/Shader/Tools.h"
#include "../Database/Player.h"
#include "../Database/Weapon.h"
#include "../Database/Charger.h"
//#include "../Database/Database.h"
//#include "../Sound/Sounds_mix.h"
//#include "../Database/Tools.cpp"

HUD::HUD()
{
	this->ammo1[0] = new ID::Drawable(35, 40);
	this->ammo1[1] = new ID::Drawable(35, 40);
	this->ammo1[2] = new ID::Drawable(35, 40);
	this->ammo2[0] = new ID::Drawable(35, 40);
	this->ammo2[1] = new ID::Drawable(35, 40);
	this->ammo2[2] = new ID::Drawable(35, 40);
	this->charger1[0] = new ID::Drawable(35, 40);
	this->charger1[1] = new ID::Drawable(35, 40);
	this->charger2[0] = new ID::Drawable(35, 40);
	this->charger2[1] = new ID::Drawable(35, 40);
	this->life[0] = new ID::Drawable(35, 40);
	this->life[1] = new ID::Drawable(35, 40);
	this->life[2] = new ID::Drawable(35, 40);
//	this->frag[0] = new ID::Drawable(35, 40);
//	this->frag[1] = new ID::Drawable(35, 40);
	this->time[0] = new ID::Drawable(35, 40);
	this->time[1] = new ID::Drawable(35, 40);
	this->time[2] = new ID::Drawable(35, 40);
}
HUD::~HUD()
{
	delete this->ammo1[0];
	delete this->ammo1[1];
	delete this->ammo1[2];
	delete this->ammo2[0];
	delete this->ammo2[1];
	delete this->ammo2[2];
	delete this->charger1[0];
	delete this->charger1[1];
	delete this->charger2[0];
	delete this->charger2[1];
	delete this->life[0];
	delete this->life[1];
	delete this->life[2];
//	delete this->frag[0];
//	delete this->frag[1];
	delete this->time[0];
	delete this->time[1];
	delete this->time[2];
	if (this->hud != NULL)
		delete this->hud;
	if (this-> avatar!= NULL)
		delete this->avatar;
}

void	HUD::Init_All(Player* player, Game* game)
{
	this->Init(player);
	this->Init_Ammo1();
	this->Init_Ammo2();
	this->Init_Charger1();
	this->Init_Charger2();
	this->Init_Life();
	this->Init_Time(game);
}

void	HUD::Init(Player* player)
{

	ID::Env*	env;

	env = ID::Env::GetInstance();
	this->hud = new ID::Drawable(800, 80);
	this->avatar = new ID::Drawable(86, 73);
	this->hud->SetPos(0, 520);
	this->avatar->SetPos(350, 524);
	this->hud->GetSurface()->LoadImage("../Resources/Pictures/hud.tga");
	this->avatar->GetSurface()->LoadImage(player->Get_Avatar());
	env->root.push_back(this->hud);
	env->root.push_back(this->avatar);
	this->player = player;
}

void	HUD::Init_Ammo1()
{
	ID::Env*	env;

	env = ID::Env::GetInstance();
	this->Set_Ammo1(this->player->Get_Weapon()->Get_Charger1()->Get_Nb_Ammo());
	this->ammo1[0]->SetPos(0, 530);
	this->ammo1[1]->SetPos(35, 530);
	this->ammo1[2]->SetPos(70, 530);
	env->root.push_back(this->ammo1[0]);
	env->root.push_back(this->ammo1[1]);
	env->root.push_back(this->ammo1[2]);
}

void	HUD::Init_Ammo2()
{
	ID::Env*	env;

	env = ID::Env::GetInstance();
	this->Set_Ammo2(this->player->Get_Weapon()->Get_Charger2()->Get_Nb_Ammo());
	this->ammo2[0]->SetPos(698, 530);
	this->ammo2[1]->SetPos(733, 530);
	this->ammo2[2]->SetPos(768, 530);
	env->root.push_back(this->ammo2[0]);
	env->root.push_back(this->ammo2[1]);
	env->root.push_back(this->ammo2[2]);
}

void	HUD::Init_Charger1()
{
	ID::Env*	env;

	env = ID::Env::GetInstance();
	this->Set_Charger1(this->player->Get_Nb_Charger1());
	this->charger1[0]->SetPos(130, 530);
	this->charger1[1]->SetPos(165, 530);
	env->root.push_back(this->charger1[0]);
	env->root.push_back(this->charger1[1]);
}

void	HUD::Init_Charger2()
{
	ID::Env*	env;

	env = ID::Env::GetInstance();
	this->Set_Charger2(this->player->Get_Nb_Charger2());
	this->charger2[0]->SetPos(600, 530);
	this->charger2[1]->SetPos(635, 530);
	env->root.push_back(this->charger2[0]);
	env->root.push_back(this->charger2[1]);
}

void	HUD::Init_Life()
{
	ID::Env*	env;

	env = ID::Env::GetInstance();
	this->Set_Life(this->player->Get_Life());
	this->life[0]->SetPos(450, 530);
	this->life[1]->SetPos(485, 530);
	this->life[2]->SetPos(520, 530);
	env->root.push_back(this->life[0]);
	env->root.push_back(this->life[1]);
	env->root.push_back(this->life[2]);
}

void	HUD::Init_Frag()
{
	ID::Env*	env;
	
	env = ID::Env::GetInstance();
	this->Set_Frag(this->player->Get_Nb_Kill());
	this->frag[0]->SetPos(260, 530);
	this->frag[1]->SetPos(295, 530);
	env->root.push_back(this->frag[0]);
	env->root.push_back(this->frag[1]);
}

void	HUD::Init_Time(Game* game)// convertir le temps en seconde
{
	ID::Env*	env;

	env = ID::Env::GetInstance();
	this->Set_Time(game->GetTime());
	this->time[0]->SetPos(225, 530);
	this->time[1]->SetPos(260, 530);
	this->time[2]->SetPos(295, 530);
	env->root.push_back(this->time[0]);
	env->root.push_back(this->time[1]);
	env->root.push_back(this->time[2]);
}

void	HUD::Set_Ammo1(int ammo)
{
	char		path[28] = "../Resources/Pictures/ .tga";
	ID::Env*	env;

	env = ID::Env::GetInstance();
	path[22] = (ammo / 100) % 10 + '0';
	this->ammo1[0]->GetSurface()->LoadImage(path);
	path[22] = ((ammo / 10) % 10) + '0';
	this->ammo1[1]->GetSurface()->LoadImage(path);
	path[22] = (ammo % 10) + '0';
	this->ammo1[2]->GetSurface()->LoadImage(path);
}

void	HUD::Set_Ammo2(int ammo)
{
	char		path[28] = "../Resources/Pictures/ .tga";
	ID::Env*	env;

	env = ID::Env::GetInstance();
	path[22] = (ammo / 100) % 10 + '0';
	this->ammo2[0]->GetSurface()->LoadImage(path);
	path[22] = ((ammo / 10) % 10) + '0';
	this->ammo2[1]->GetSurface()->LoadImage(path);
	path[22] = (ammo % 10) + '0';
	this->ammo2[2]->GetSurface()->LoadImage(path);
}

void	HUD::Set_Life(int life)
{
	ID::Env*	env;
	char		path[28] = "../Resources/Pictures/ .tga";

	env = ID::Env::GetInstance();
	path[22] = (life / 100) % 10 + '0';
	this->life[0]->GetSurface()->LoadImage(path);
	path[22] = ((life / 10) % 10) + '0';
	this->life[1]->GetSurface()->LoadImage(path);
	path[22] = (life % 10) + '0';
	this->life[2]->GetSurface()->LoadImage(path);
}

void	HUD::Set_Frag(int frag)
{
	ID::Env*	env;
	char		path[28] = "../Resources/Pictures/ .tga";

	env = ID::Env::GetInstance();
	path[22] = ((frag / 10) % 10) + '0';
	this->frag[0]->GetSurface()->LoadImage(path);
	path[22] = (frag % 10) + '0';
	this->frag[1]->GetSurface()->LoadImage(path);
}

void	HUD::Set_Charger1(int charger)
{
	ID::Env*	env;
	char		path[28] = "../Resources/Pictures/ .tga";

	env = ID::Env::GetInstance();
	path[22] = ((charger / 10) % 10) + '0';
	this->charger1[0]->GetSurface()->LoadImage(path);
	path[22] = (charger % 10) + '0';
	printf("%s\n",path);
	this->charger1[1]->GetSurface()->LoadImage(path);
}

void	HUD::Set_Charger2(int charger)
{
	ID::Env*	env;
	char		path[28] = "../Resources/Pictures/ .tga";

	env = ID::Env::GetInstance();
	path[22] = ((charger / 10) % 10) + '0';
	this->charger2[0]->GetSurface()->LoadImage(path);
	path[22] = (charger % 10) + '0';
	this->charger2[1]->GetSurface()->LoadImage(path);
}

void	HUD::Set_Time(int time)
{
	ID::Env*	env;
	char		path[28] = "../Resources/Pictures/ .tga";

	env = ID::Env::GetInstance();
	path[22] = (time / 100) % 10 + '0';
	this->time[0]->GetSurface()->LoadImage(path);
	path[22] = ((time / 10) % 10) + '0';
	this->time[1]->GetSurface()->LoadImage(path);
	path[22] = (time % 10) + '0';
	this->time[2]->GetSurface()->LoadImage(path);
}

