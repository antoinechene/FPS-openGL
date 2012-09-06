#include "Ball.h"
#include "StaticObj.h"
#include "Polygon.h"
#include <iostream>
#include <vector>
#include "HitBox.h"

StaticObj::StaticObj()
{
	this->_type = Object::O_STATIC;
}


StaticObj::StaticObj(Vec3f p, Vec3f r, Vec3f s) : SolidObj(p, r, s)
{

}

StaticObj::~StaticObj(void)
{

}
bool	StaticObj::GenerateHitBox(void)
{
//	try
//	{
//		this->_hitbox = new HitBox(10.f, this->pos);
//	}
//	catch (std::bad_alloc&)
//	{
//		return (false);
//	}
	return (true);
}
void	StaticObj::AddHitbox(HitBox* Hit)
{
	this->_hitbox.push_back(Hit);
}

void	StaticObj::DrawHitbox(void)
{
	std::list<HitBox*>::iterator	it = this->_hitbox.begin();
	std::list<HitBox*>::iterator	it_end = this->_hitbox.end();

	glColor3f(1.0f, 0.0f, 0.0f);

	while (it != it_end)
	{
		glPushMatrix();

		glTranslatef((*it)->__pos[0], (*it)->__pos[1], (*it)->__pos[2]);
		glColor3f(1.0f, 0.0f, 0.0f);
		glutWireCube((*it)->GetSize());
		glPopMatrix();
		++it;
	}

}

bool	StaticObj::__TestSphereCollision(HitBox* h1, Ball* b)
{
	Polygon**	points = this->m->GetPoly();
	Vec3f		vert[3];
	GLfloat		rr;
	Vec3f		v;
	GLfloat		d[4];
	GLfloat		e[4];
	bool		sep[7];
	GLfloat		val[6];
	Vec3f		AB;
	Vec3f		BC;
	Vec3f		CA;
	Vec3f		Q[6];
	Vec3f		pos_ball;

	pos_ball = b->pos;
	vert[0] = points[h1->__id]->Mesh[0]->GetPoint() - b->pos;
	vert[1] = points[h1->__id]->Mesh[1]->GetPoint() - b->pos;
	vert[2] = points[h1->__id]->Mesh[2]->GetPoint() - b->pos;
	rr = b->radius * b->radius;
	v = (vert[1] - vert[0]).cross(vert[2] - vert[0]);
	d[0] = vert[0].dot(v);
	e[0] = v.dot(v);
	sep[0] = (d[0] * d[0]) > (rr * e[0]);
	if (sep[0])
		return (false);
	val[0] = vert[0].dot(vert[0]);
	val[1] = vert[0].dot(vert[1]);
	val[2] = vert[0].dot(vert[2]);
	val[3] = vert[1].dot(vert[1]);
	val[4] = vert[1].dot(vert[2]);
	val[5] = vert[2].dot(vert[2]);
	sep[1] = (val[0] > rr) && (val[1] > val[0]) && (val[2] > val[0]);
	sep[2] = (val[3] > rr) && (val[1] > val[3]) && (val[4] > val[3]);
	sep[3] = (val[5] > rr) && (val[2] > val[5]) && (val[4] > val[5]);
	if (sep[1] || sep[2] || sep[3])
		return (false);
	AB = vert[1] - vert[0];
	BC = vert[2] - vert[1];
	CA = vert[0] - vert[2];
	d[1] = val[1] - val[0];
	d[2] = val[4] - val[3];
	d[3] = val[2] - val[5];
	e[1] = AB.dot(AB);
	e[2] = BC.dot(BC);
	e[3] = CA.dot(CA);
	Q[0] = vert[0] * e[1] - d[1] * AB;
	Q[1] = vert[1] * e[2] - d[2] * BC;
	Q[2] = vert[2] * e[3] - d[3] * CA;
	Q[3] = vert[2] * e[1] - Q[1];
	Q[4] = vert[0] * e[2] - Q[2];
	Q[5] = vert[1] * e[3] - Q[3];
	sep[4] = (Q[0].dot(Q[0]) > rr * e[1] * e[1]) && (Q[0].dot(Q[3]) > 0);
	sep[5] = (Q[1].dot(Q[1]) > rr * e[2] * e[2]) && (Q[1].dot(Q[4]) > 0);
	sep[6] = (Q[2].dot(Q[2]) > rr * e[3] * e[3]) && (Q[2].dot(Q[5]) > 0);
	if (!(sep[0] || sep[1] || sep[2] || sep[3] || sep[4] || sep[5] || sep[6]))
	{
		this->impact = h1->__id;
		return (true);
	}

	return (false);
	
}

void	StaticObj::Collision(HitBox* h1, SolidObj* obj, HitBox*)
{
	if (obj->GetType() == Object::O_SPHERE && this->__TestSphereCollision(h1, (Ball*)obj))
		this->__ApplySphereCollision((Ball*)obj);
}

void	StaticObj::__ApplySphereCollision(Ball* b)
{
	Vec3f	n = (this->m->GetPoly()[this->impact]->Mesh[0]->GetPoint() - this->m->GetPoly()[this->impact]->Mesh[1]->GetPoint()).cross((this->m->GetPoly()[this->impact]->Mesh[1]->GetPoint() - this->m->GetPoly()[this->impact]->Mesh[2]->GetPoint())).normalize();

	b->velocity -= 2 * n * b->velocity.dot(n) * 0.8f;
}
