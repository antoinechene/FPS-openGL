#include <GL/glut.h>
#include "../Objects/FBXLoader.h"
#include "../HUD/Game.h"
#include "../HUD/Hud.h"
#include "../Objects/Display.h"
#include "../map/Map.h"
//#include "../Objects/Ball.h"
//#include "../Objects/Shader/Tools.h"
#include "../Database/Player.h"
//#include "../Database/Weapon.h"
//#include "../Database/Charger.h"
#include "../Database/Database.h"
#include "../Sound/Sounds_mix.h"
//#include "../Database/Tools.h"


int	main(int argc, char** argv)
{
	Display*	disp;
	Map*		M;
	Player*		P1;
	Vec3f		pos(0, 0, 0);
	Vec3f		rot(0, 0, 0);
	Vec3f		scale(0, 0, 0);
	Vec3f		vit(0, 0, 0);
	Database*	Dat;
	ID::Env*	env;
//	HUD*		hud;

	env = ID::Env::GetInstance();
	Dat = Database::GetInstance();
	if (Dat->Init() == -1)
		return (42);
	disp = Display::GetInstance();

	P1 = new Player("fabus", (char*)"../Resources/Pictures/avatar.tga", 1, pos, rot, scale, vit, 10.0f);
	M = new Map(0, "Dude", "../fbx/humanoid.fbx");
	disp->hud = new HUD();
	disp->game = new Game(0, M, 5000000, 16);
	disp->game->S = Sounds::GetInstance();
	disp->game->S->init();
	disp->game->S->set_theme(0);
	disp->game->AddPlayer(P1);

	disp->Init(argc, argv);
	glutMainLoop();
	return (0);
}
