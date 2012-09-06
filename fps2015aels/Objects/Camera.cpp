#include "HitBox.h"
#include "Camera.h"
#include "Ball.h"

Camera::Camera(Vec3f p, Vec3f r, Vec3f s, Vec3f v, GLfloat m, Vec3f t, Vec3f f, Vec3f l,
	       GLfloat fov, GLfloat near, GLfloat far,
	       GLfloat width, GLfloat height, GLfloat speed_forward, GLfloat speed_side, GLfloat sensx, GLfloat sensy,
	       GLfloat phi, GLfloat theta, bool jumping)
			: NewtonObj(p, r, s, v, m), target(t),
			  forward(f), left(l),
			  fov(fov), near(near), far(far),
			  width(width), height(height),
			  speed_forward(speed_forward), speed_side(speed_side), sensitivityx(sensx), sensitivityy(sensy),
			  phi(phi), theta(theta), jumping(jumping)
{

}

Camera::~Camera(void)
{

}

bool	Camera::GenerateHitBox(void)
{
	try
	{
		this->_hitbox.push_back(new HitBox(1.f,
		this->pos, this, 0));
	}
	catch (std::bad_alloc&)
	{
		return (false);
	}
	return (true);
}

void	Camera::Collision(HitBox*, SolidObj* obj, HitBox*)
{
	if (obj->GetType() == Object::O_SPHERE && this->__TestSphereCollision((Ball*)obj))
		this->__ApplySphereCollision((Ball*)obj);
}

bool	Camera::__TestSphereCollision(Ball* b)
{
	Vec3f	bound = this->pos;

	bound[1] -= 3.f;
	if ((bound - b->pos).magnitudeSquared() <
			(b->radius + 1.f) * (b->radius + 1.f))
		return (true);
	return (false);
}

void	Camera::__ApplySphereCollision(Ball* b)
{
	Vec3f	bound = this->pos;

	bound[1] -= 3.f;

	Vec3f		c = (b->pos - bound).normalize();
	GLfloat		d = c.dot((b->velocity - this->forward * this->speed_forward));

	b->velocity -= ((this->mass * d) / (b->mass + this->mass)) * (2 * c) * 1.05f;
	this->velocity += ((b->mass * d) / (this->mass + b->mass)) * (2 * c) * 1.05f;

}
