#include <new>
#include "Ball.h"
#include "StaticObj.h"
#include "Polygon.h"

Ball::Ball(Vec3f pos, Vec3f rot, Vec3f sca, Vec3f vel, GLfloat mas, GLfloat rad)
	   : NewtonObj(pos, rot, sca, vel, mas), radius(rad)
{
	this->_type = Object::O_SPHERE;
}

Ball::~Ball(void)
{

}

bool	Ball::GenerateHitBox(void)
{
	try
	{
		this->_hitbox.push_back(new HitBox(this->radius,
		this->pos, this, 0));
	}
	catch (std::bad_alloc&)
	{
		return (false);
	}
	return (true);
}

bool	Ball::__TestSphereCollision(Ball* b)
{
	if ((this->pos - b->pos).magnitudeSquared() <
			(this->radius + b->radius) * (this->radius + b->radius))
		return ((this->velocity - b->velocity).dot(this->pos - b->pos) < 0);
	return (false);
}

bool	Ball::__TestCameraCollision(Camera* c)
{
	Vec3f	bound = c->pos;

	bound[1] -= 3.f;
	if ((this->pos - bound).magnitudeSquared() <
			(this->radius + 1.f) * (this->radius + 1.f))
		return (true);
	return (false);
}

void	Ball::Collision(HitBox*, SolidObj* obj, HitBox* h2)
{
	if (obj->GetType() == Object::O_SPHERE && this->__TestSphereCollision((Ball*)obj))
		this->__ApplySphereCollision((Ball*)obj);
	if (obj->GetType() == Object::O_CAMERA && this->__TestCameraCollision((Camera*)obj))
		this->__ApplyCameraCollision((Camera*)obj);
	if (obj->GetType() == Object::O_STATIC && this->__TestStaticObjCollision(h2, (StaticObj*)obj))
		this->__ApplyStaticObjCollision((StaticObj*)obj);
}

void	Ball::__ApplySphereCollision(Ball* b)
{
	Vec3f		c = (this->pos - b->pos).normalize();
	GLfloat		d = c.dot((this->velocity - b->velocity));

	this->velocity -= (((b->mass * d) / (this->mass + b->mass)) * (2 * c) * 0.5f) - c * 0.01f;
	b->velocity += (((this->mass * d) / (this->mass + b->mass)) * (2 * c) * 0.5f) + c * 0.01f;
}

void	Ball::__ApplyCameraCollision(Camera* cam)
{
	Vec3f	bound = cam->pos;

	bound[1] -= 3.f;

	Vec3f		c = (this->pos - bound).normalize();
	GLfloat		d = c.dot((this->velocity - cam->forward * cam->speed_forward));

	this->velocity -= ((cam->mass * d) / (this->mass + cam->mass)) * (2 * c) * 0.5f;
	cam->velocity += ((this->mass * d) / (this->mass + cam->mass)) * (2 * c) * 0.5f;
}

bool	Ball::__TestStaticObjCollision(HitBox* h1, StaticObj* obj)
{
	Polygon**	points = obj->m->GetPoly();
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

	pos_ball = this->pos;
	vert[0] = points[h1->__id]->Mesh[0]->GetPoint() - this->pos;
	vert[1] = points[h1->__id]->Mesh[1]->GetPoint() - this->pos;
	vert[2] = points[h1->__id]->Mesh[2]->GetPoint() - this->pos;
	rr = this->radius * this->radius;
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

void	Ball::__ApplyStaticObjCollision(StaticObj* obj)
{
	Vec3f	n = (obj->m->GetPoly()[obj->impact]->Mesh[0]->GetPoint() - obj->m->GetPoly()[obj->impact]->Mesh[1]->GetPoint()).cross((obj->m->GetPoly()[obj->impact]->Mesh[1]->GetPoint() - obj->m->GetPoly()[obj->impact]->Mesh[2]->GetPoint())).normalize();

	this->velocity -= 2 * n * this->velocity.dot(n) * 0.8f;
}

