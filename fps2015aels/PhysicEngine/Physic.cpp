#include <typeinfo>
#include <GL/glut.h>
#include "../Objects/Camera.h"
#include "../EventHandler/EventHandler.h"
#include "Physic.h"
#include "../Objects/Ball.h"

extern std::vector<Ball*>	balls;

Physic::Physic(Camera* cam) : __octree(Octree(Vec3f(-1000.f, -1000.f, -1000.f),
					      Vec3f(1000.f, 1000.f, 1000.f), 1)),
			      __nb_newton_objs(0),
			      __camera(cam)
{
	cam->GenerateHitBox();
	this->AddObject((SolidObj*)cam);
}

Physic::~Physic(void)
{

}

void	Physic::AddObject(SolidObj* obj)
{
	if (obj == NULL)
		return ;
	try
	{
		NewtonObj*	n_obj = dynamic_cast<NewtonObj*>(obj);
		this->__newton_objs.push_back(n_obj);
		this->__nb_newton_objs++;
	}
	catch (std::bad_cast&)
	{
		this->__solid_objs.push_back(obj);
	}
	this->__octree.Add(obj);
}

void	Physic::AddObject(Plane* obj)
{
	if (obj == NULL)
		return ;
	this->__solid_objs.push_back(obj);
	this->__octree.Add(obj);
}

void	Physic::AddObject(StaticObj* obj)
{
	if (obj == NULL)
		return ;
	this->__solid_objs.push_back(obj);
	this->__octree.Add(obj);
}

void	Physic::DelObject(SolidObj*)
{

}

void	Physic::MoveWorld(GLfloat dt)
{
	std::vector<NewtonObj*>::iterator		it = this->__newton_objs.begin();
	std::vector<NewtonObj*>::iterator		it_end = this->__newton_objs.end();
	Vec3f						old_pos;

	while (it != it_end)
	{
		old_pos = (*it)->pos;
		(*it)->pos += (*it)->velocity * dt;
		(*((*it)->_hitbox.begin()))->__pos = (*it)->pos;
		this->__octree.Move((SolidObj*)*it);
		++it;
	}
}

void	Physic::__ApplyGravity(void)
{
	std::vector<NewtonObj*>::iterator	it;
	std::vector<NewtonObj*>::iterator	it_end;

	it = this->__newton_objs.begin();
	it_end = this->__newton_objs.end();
	while (it != it_end)
	{
		(*it)->velocity -= Vec3f(0.f, 8.f * 0.01f, 0.f);
		++it;
	}
}

void	Physic::Update(void)
{
	this->__ApplyGravity();
	this->__ApplyCollision();
}

void	Physic::__ApplyCollision(void)
{
	std::list<ObjectPair>	obj_pair;
	std::list<ObjectPair>::iterator	it;
	std::list<ObjectPair>::iterator	it_end;
	std::vector<Ball*>::iterator		it_ball = balls.begin();
	std::vector<Ball*>::iterator		it_ball_end = balls.end();

	while (it_ball != it_ball_end)
	{
		if ((*it_ball)->pos[1] < -6.f + (*it_ball)->radius && (*it_ball)->velocity[1] < 0.f)
		{
			(*it_ball)->velocity[1] = -(*it_ball)->velocity[1] * 0.5f;
			(*it_ball)->velocity *= 0.992f;
			if ((*it_ball)->velocity[0] * (*it_ball)->velocity[0] + (*it_ball)->velocity[2] * (*it_ball)->velocity[2] < 0.05f)
				(*it_ball)->velocity = Vec3f(0.f, 0.f, 0.f);
		}
		if ((*it_ball)->pos[1] < -6.f + (*it_ball)->radius)
			(*it_ball)->pos[1] = -6.f + (*it_ball)->radius;
		++it_ball;
	}
	this->__octree.CheckCollision(&obj_pair);
	it = obj_pair.begin();
	it_end = obj_pair.end();
	while (it != it_end)
	{
		it->o1->Collision(it->h1, it->o2, it->h2);
		++it;
	}
	if (this->__camera->pos[1] < -2.f && this->__camera->velocity[1] < 0.f)
	{
		this->__camera->pos[1] = -2.f;
		this->__camera->velocity[1] = 0.f;
		if (this->__camera->jumping == true)
			this->__camera->jumping = false;
	}
}

