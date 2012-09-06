#include <GL/glut.h>
#include "EventHandler.h"

#include "../Objects/Display.h"
#include "../Database/Player.h"
#include "../game/Game.h"
#include "../Database/Weapon.h"
#include "../Database/Charger.h"
#include "../Sound/Sounds_mix.h"

#include <vector>
#include "../Objects/Ball.h"
#include "../Objects/Camera.h"
#include "../PhysicEngine/Physic.h"


extern std::vector<Ball*>	balls;
extern Camera			camera;
extern Physic			g_phys;

EventHandler::EventHandler(void)
{
	ID::Init(SDL_INIT_EVERYTHING);
	ID::InitWrappers();
//	this->__we->Init();
}

EventHandler::~EventHandler(void)
{

}

bool	EventHandler::Init(void)
{
	this->__key_bind['w'] = EventHandler::E_FORWARD;
	this->__key_bind['s'] = EventHandler::E_BACKWARD;
	this->__key_bind['a'] = EventHandler::E_LEFT;
	this->__key_bind['d'] = EventHandler::E_RIGHT;
	this->__key_bind[' '] = EventHandler::E_JUMP;
	this->__key_bind['e'] = EventHandler::E_ACTION;
	this->__key_bind['+'] = EventHandler::E_CHANGE_ANIM;
	this->__key_bind['p'] = EventHandler::E_PLAY_ANIM;


	this->__mouse_bind[GLUT_RIGHT_BUTTON] = EventHandler::E_NONE;
	this->__mouse_bind[GLUT_LEFT_BUTTON] = EventHandler::E_SHOT;

	this->__event_map[EventHandler::E_FORWARD] = false;
	this->__event_map[EventHandler::E_BACKWARD] = false;
	this->__event_map[EventHandler::E_LEFT] = false;
	this->__event_map[EventHandler::E_RIGHT] = false;
	this->__event_map[EventHandler::E_JUMP] = false;
	this->__event_map[EventHandler::E_SHOT] = false;
	this->__event_map[EventHandler::E_ACTION] = false;
	this->__event_map[EventHandler::E_CHANGE_ANIM] = false;
	this->__event_map[EventHandler::E_PLAY_ANIM] = false;

	return (true);
}

void	EventHandler::KeyboardFunc(unsigned char key, int, int)
{
	ID::Env*	env;
	EventHandler*	s_event = EventHandler::GetInstance();
	Display*	disp = Display::GetInstance();

	env = ID::Env::GetInstance();
	if (disp->InGame)
		s_event->__event_map[s_event->__key_bind[key]] = true;
	else
	{
		s_event->__ev.type = ID::EVENT_KEY_DOWN;
		s_event->__ev.keyDown.keysym.sym = (ID::Key)key;
		env->KeyDown(&(s_event->__ev));
	}
}

void	EventHandler::KeyboardUpFunc(unsigned char key, int, int)
{
	ID::Env*	env;
	EventHandler*	s_event = EventHandler::GetInstance();
	Display*	disp = Display::GetInstance();

	env = ID::Env::GetInstance();
	if (disp->InGame)
		s_event->__event_map[s_event->__key_bind[key]] = false;
	else
	{
		s_event->__ev.type = ID::EVENT_KEY_UP;
		s_event->__ev.keyUp.keysym.sym = (ID::Key)key;
		env->KeyUp(&(s_event->__ev));
	}
}

void	EventHandler::MouseFunc(int but, int state, int x, int y)
{
	EventHandler*			s_event = EventHandler::GetInstance();
	Display*			disp;
	std::list<Player*>::iterator	it;
	ID::Env*			env;

	env = ID::Env::GetInstance();
	disp = Display::GetInstance();
	it = disp->game->GetPlayerList()->begin();
	if (disp->InGame)
	{
		if (but == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
		{
			if ((*it)->Get_Weapon()->Get_Charger1()->Get_Nb_Ammo() > 0)
			{
				disp->game->S->play_distant_sound(0, 0, 0);
				(*it)->Fire(0);
				Ball*	ball = new Ball(Vec3f(camera.pos[0] + camera.forward[0], camera.pos[1] - 1.f, camera.pos[2]),
							Vec3f(0.f, 0.f, 0.f), Vec3f(1.f, 1.f, 1.f),
							Vec3f(camera.forward[0] * ((GLfloat)rand() / (GLfloat)RAND_MAX / 50.f + 0.99f) * 100.f,
							      camera.forward[1] * 100.f,
							      camera.forward[2] * ((GLfloat)rand() / (GLfloat)RAND_MAX / 50.f + 0.99f) * 100.f),
							0.5f, 0.5f * 0.9f);
				ball->GenerateHitBox();
				balls.push_back(ball);
				g_phys.AddObject((SolidObj*)ball);
			}
			else
			{
				(*it)->Reload(0);
				disp->game->S->play_distant_sound(1, 0, 0);
			}
		}
	}
	else
	{
		if (state == GLUT_DOWN)
		{
			s_event->__ev.type = ID::EVENT_CLICK_DOWN;
			s_event->__ev.clickDown.button = (ID::Mouse_Button)but;
			s_event->__ev.clickDown.x = x;
			s_event->__ev.clickDown.y = y;
			env->ClickDown(&(s_event->__ev));
		}
		else if (state == GLUT_UP)
		{
			s_event->__ev.type = ID::EVENT_CLICK_UP;
			s_event->__ev.clickDown.button = (ID::Mouse_Button)but;
			s_event->__ev.clickDown.x = x;
			s_event->__ev.clickDown.y = y;
			env->ClickUp(&(s_event->__ev));
		}
	}
}


