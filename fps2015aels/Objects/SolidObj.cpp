#include "SolidObj.h"

SolidObj::SolidObj() : Object(), _hitbox(NULL)
{

}


SolidObj::SolidObj(Vec3f p, Vec3f r, Vec3f s) : Object(p, r, s, true), _hitbox(NULL)
{

}

SolidObj::~SolidObj(void)
{
//	if (this->_hitbox != NULL)
//		delete this->_hitbox;
}

void	SolidObj::Collision(HitBox*, SolidObj*, HitBox*)
{
}

