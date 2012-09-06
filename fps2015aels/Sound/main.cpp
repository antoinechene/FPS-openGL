#include "../Database/Database.h"
#include "Sounds_mix.h"
#include <iostream>
#include <GL/glut.h>

bool	CanPlay();

void	Keyboard(unsigned char key, int x, int y)
{

	if (!CanPlay())
		return;
//	printf("yo\n");
	if (key == 'w')
		Sounds::GetInstance()->play_distant_sound(0, 0, 0);
	else if (key == 'a')
		Sounds::GetInstance()->play_distant_sound(0, 270, 50);
	else if (key == 's')
		Sounds::GetInstance()->play_distant_sound(0, 180, 100);
	else if (key == 'd')
		Sounds::GetInstance()->play_distant_sound(0, 90, 50);
	else if (key == 'q')
		Sounds::GetInstance()->play_distant_sound(0, 315, 50);
	else if (key == 'e')
		Sounds::GetInstance()->play_distant_sound(0, 45, 50);
//	Mix_SetPosition(MIX_CHANNELS_POST, 0, 0);*/
}

void	Keyboard_s(int key, int x, int y)
{

}

void	Display()
{

}

bool	CanPlay()
{
	static double	current_time = 0;
	static double	last_time = 0;
	double		res;

	last_time = current_time;
	current_time = (double)glutGet(GLUT_ELAPSED_TIME);
	res = (current_time -last_time);
	if (res > 500)
	{
		return (true);
	}
	else
		return (false);
}


int	main(int argc, char** argv)
{
	Database*	database;

	database = Database::GetInstance();
	database->Init();
	glutInit(&argc, argv);
	if (Sounds::GetInstance() == NULL)
		return -1;
//	sound1->init();
//	sound2->init();
//	sound1->set_theme(SONG_DRS);
//	sound2->set_theme(SONG_OFF);

	Sounds::GetInstance()->init();
	Sounds::GetInstance()->set_theme(0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 800);
	glutCreateWindow("test musique");
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Keyboard_s);
	glutDisplayFunc(Display);
	glutMainLoop();
}
