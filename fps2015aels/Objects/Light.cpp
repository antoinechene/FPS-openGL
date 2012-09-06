#include "Light.h"

Light::Light(Vec3f pos, Vec3f rot, Vec3f sca, GLfloat r, GLfloat g, GLfloat b, GLfloat a) : GhostObj(pos, rot, sca)
{
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
	this->color[3] = a;
}

Light::~Light(void)
{

}

