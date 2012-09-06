#include "Object.h"

Object::Object()
{
	this->m = NULL;
}
Object::Object(Vec3f p, Vec3f r, Vec3f s, bool) : pos(p), rot(r), scale(s)
{
	this->m = NULL;
}

Object::~Object(void)
{
	if (this->m != NULL)
		delete this->m;
}

