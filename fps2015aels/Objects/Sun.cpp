#include "Sun.h"

Sun::Sun(Vec3f rot, GLfloat r, GLfloat g, GLfloat b, GLfloat a) : Light(Vec3f(0.f, 0.f, 0.f), rot, Vec3f(0.f, 0.f, 0.f), r, g, b, a)
{

}

Sun::~Sun(void)
{

}

