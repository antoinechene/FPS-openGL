#include <GL/glut.h>
#include "Vec3f.h"
#include "HitBox.h"

HitBox::HitBox(GLfloat s, Vec3f p, SolidObj* parent, int id) : __size(s), __pos(p), __parent(parent), __id(id)
{
}

HitBox::~HitBox(void)
{

}

