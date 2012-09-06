#include <GL/glut.h>
#include "NewtonObj.h"

NewtonObj::NewtonObj(Vec3f p, Vec3f r, Vec3f s, Vec3f v, GLfloat m) : PhysObj(p, r, s, v), mass(m)
{

}

NewtonObj::~NewtonObj(void)
{

}

