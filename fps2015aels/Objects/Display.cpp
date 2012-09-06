#include <GL/glew.h>
#include <GL/glut.h>

#include "Display.h"
#include "Object.h"
#include "Camera.h"
#include <math.h>
#include "Ball.h"
#include <iostream>
#include <vector>
#include "Light.h"
#include "../PhysicEngine/Octree.h"
#include "../game/Game.h"
#include "../map/Map.h"
#include "../Database/Player.h"
#include "../Database/Weapon.h"
#include "../Database/Charger.h"
#include "../Sound/Sounds_mix.h"
#include "../PhysicEngine/Physic.h"
#include "../EventHandler/EventHandler.h"
#include "../menu/FirstMenu.h"
#include "../menu/ServerMenu.h"
#include "../menu/Option_Menu.h"
#include "Plane.h"
#include "../HUD/Hud.h"

#define GRAVITY			-24.f
#define TIME_UP			0.001f


#define MOUSE_WARP_OFFSET	500
GLfloat			g_time = 0;

std::vector<Ball*>	balls;
std::vector<Light>	lights;
Camera			camera;
Physic			g_phys(&camera);



Display::Display()
{
	this->InGame = false;
	this->hud = new HUD();
	this->height = 600;
	this->width = 800;
}


Display::~Display()
{
	delete this->game;
}

void	Display::InitMenu(void)
{
	ServerMenu*	smenu;
	FirstMenu*	fmenu;
	OptionMenu*	omenu;

	smenu = new ServerMenu();
	fmenu = new FirstMenu();
	omenu = new OptionMenu();
	this->menu.push_back(fmenu);
	this->menu.push_back(smenu);
	this->menu.push_back(omenu);
//	test = FirstMenu();
//	test = ServerMenu();
//	test = new FirstMenu();
	this->menu[1]->Construct();
	this->menu[2]->Construct();
	this->menu[0]->Construct();
	this->menu[1]->Rem_Win();
	this->menu[2]->Rem_Win();
}


void	Display::Exit(void)
{
	Display::Kill();
}

int	Display::Init(int argc, char** argv)
{
	GLenum err;
	Display*	disp;
	std::list<Player*>::iterator	it;

	disp = Display::GetInstance();
	it = disp->game->GetPlayerList()->begin();
	EventHandler*	s_event = EventHandler::GetInstance();
	lights.push_back(Light());
	s_event->Init();
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(this->width, this->height);
	glutCreateWindow("fps");
	glutIgnoreKeyRepeat(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutDisplayFunc(&RenderScene);
	glutKeyboardFunc(EventHandler::KeyboardFunc);
	glutReshapeFunc(&ReshapeFunc);
	glutKeyboardUpFunc(EventHandler::KeyboardUpFunc);
	glutPassiveMotionFunc(&PassiveMotionFunc);
	glutMouseFunc(EventHandler::MouseFunc);
	glutTimerFunc(25, &TimerFunc, 0);
	err = glewInit();
	if (err != GLEW_OK)
		return (42);
	glViewport(0, 0, this->width, this->height);
	gluPerspective(45.0f, (GLfloat) this->width / (GLfloat)this->height, 1.0f, 1000.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);
//	this->hud->Init_All(*it, this->game);
	this->InitMenu();
	return (0);
}


void	Display::RenderScene(void)
{
	size_t				i;
	size_t				size;
	Display*			disp;
	GLfloat				ambient_color[] = {1.0f, 1.0f, 1.0f, 1.f};
	GLfloat				diffuse_color[] = {1.0f, 1.0f, 1.0f, 1.f};
//	GLfloat				specular_color[] = {0.5f, 0.5f, 0.5f, 1.f};
	GLfloat				light_pos[] = {-0.0f, 50.f, 100.f, 1.f};
	std::vector<Object*>*		obj;
	std::vector<Ball*>::iterator	it;
	std::vector<Ball*>::iterator	it_end;
	ID::Env*			env;

	disp = Display::GetInstance();
	env = ID::Env::GetInstance();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	if (disp->InGame)
	{
		if (disp->game->EndGame())
			exit(42);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glShadeModel(GL_SMOOTH);
	//	gluPerspective(40.0f, 4.0 / 3.0f, 0.01, 1000.0f);//ce truc est ouf 2D
		gluLookAt(camera.pos[0], camera.pos[1], camera.pos[2],
			  camera.target[0], camera.target[1], camera.target[2],
			  0, 1, 0);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_color);
	//	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_color);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		it = balls.begin();
		it_end = balls.end();
		while (it != it_end)
		{
			glPushMatrix();
			glTranslatef((*it)->pos[0], (*it)->pos[1], (*it)->pos[2]);
			glutSolidSphere((*it)->radius, 20, 20);
			glPopMatrix();
			++it;
		}
		obj = disp->game->GetCurrentMap()->GetObjectList();
		size = obj->size();
		i = 0;
		glPushMatrix();
		while (i < size)
		{
			disp->ApllyMat((*obj)[i]);
			(*obj)[i]->m->Draw();
		//	((StaticObj*)(*obj)[i])->DrawHitbox();
			++i;
			glPopMatrix();
		}
		glPopMatrix();
		disp->game->ActualizeTime();
		disp->Disable3D();
		env->RefreshScreen();
		disp->Enable3D();
		disp->ReshapeFunc(disp->width, disp->height);
	}
	else
	{
		disp->Disable3D();
		env->RefreshScreen();
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

void	Display::ApllyMat(Object* obj)
{
	glPushMatrix();
	glMultMatrixf(obj->m->GetMatrice());
}


void	Display::PassiveMotionFunc(int x, int y)
{
	static const Vec3f	up(0.f, 1.f, 0.f);
	GLfloat			tmp;
	Display*		disp = Display::GetInstance();

	camera.theta += (x - MOUSE_WARP_OFFSET) * camera.sensitivityx;
	camera.phi -= (y - MOUSE_WARP_OFFSET) * camera.sensitivityy;
	if (camera.phi > 89.f)
		camera.phi = 89.f;
	else if (camera.phi < -89.f)
		camera.phi = -89.f;
	tmp = cos(camera.phi * M_PI / 180.f);
	camera.forward[1] = sin(camera.phi * M_PI / 180.f);
	camera.forward[0] = tmp * cos(camera.theta * M_PI / 180.f);
	camera.forward[2] = tmp * sin(camera.theta * M_PI / 180.f);
	camera.left = up.cross(camera.forward);
	camera.left.normalize();
	camera.target = camera.pos + camera.forward;
	if (disp->InGame)
	{
		if (x != MOUSE_WARP_OFFSET && y != MOUSE_WARP_OFFSET)
			glutWarpPointer(MOUSE_WARP_OFFSET, MOUSE_WARP_OFFSET);
	}
}

void	Display::TimerFunc(int)
{
	static GLfloat	time = 0.f;
	GLfloat		t;

	t = 0.025f;
	while (t > 0)
	{
		if (time <= t)
		{
			MoveWorld(time);
			g_phys.Update();
			t -= time;
			time = 0.001f;
		}
		else
		{
			MoveWorld(time);
			time -= t;
			t = 0.f;
		}
	}
	glutTimerFunc(25, TimerFunc, 0);
	glutPostRedisplay();
}


void	Display::MoveWorld(GLfloat dt)
{
	EventHandler*					s_event = EventHandler::GetInstance();
	std::map<EventHandler::EVENT_TYPE, bool>*	events;

	events = s_event->GetCurrentEvents();
	if ((*events)[EventHandler::E_FORWARD] == true)
	{
		camera.pos[0] += camera.forward[0] *
					  camera.speed_forward * dt;
		camera.pos[2] += camera.forward[2] *
					  camera.speed_forward * dt;
	}
	if ((*events)[EventHandler::E_BACKWARD] == true)
	{
		camera.pos[0] -= camera.forward[0] *
					  camera.speed_forward * dt;
		camera.pos[2] -= camera.forward[2] *
					  camera.speed_forward * dt;
	}
	if ((*events)[EventHandler::E_LEFT] == true)
	{
		camera.pos[0] += camera.left[0] *
					  camera.speed_side * dt;
		camera.pos[2] += camera.left[2] *
					  camera.speed_side * dt;
	}
	if ((*events)[EventHandler::E_RIGHT] == true)
	{
		camera.pos[0] -= camera.left[0] *
					  camera.speed_side * dt;
		camera.pos[2] -= camera.left[2] *
					  camera.speed_side * dt;
	}
	if ((*events)[EventHandler::E_JUMP] == true)
	{
		camera.velocity[1] = 20.f;
		camera.jumping = true;
	}
	camera.velocity[0] = 0.f;
	camera.velocity[2] = 0.f;
//	camera.pos += camera.velocity * dt;
	camera.target = camera.pos + camera.forward;
	lights[0].pos = camera.pos;
	g_phys.MoveWorld(dt);

}

void	Display::ReshapeFunc(int w, int h)
{
	Display*			disp;

	disp = Display::GetInstance();
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera.fov, (float)w / (float)h, camera.near, camera.far);
	disp->width = w;
	disp->height = h;
}

void	Display::Disable3D(void)
{

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void	Display::Enable3D(void)
{
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}
