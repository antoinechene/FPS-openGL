#include "PhysObj.h"
#include "Vec3f.h"

PhysObj::PhysObj(Vec3f p, Vec3f r, Vec3f s, Vec3f v) : SolidObj(p, r, s), velocity(v)
{

}

PhysObj::~PhysObj(void)
{

}

