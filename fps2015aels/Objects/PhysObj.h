#ifndef __PHYSOBJ_H__
#define __PHYSOBJ_H__

#include "SolidObj.h"
#include "Vec3f.h"

class	PhysObj : public SolidObj
{
public:
			PhysObj(Vec3f, Vec3f, Vec3f, Vec3f);
	virtual		~PhysObj(void);
	virtual bool	GenerateHitBox(void) = 0;
	virtual void	Collision(HitBox*, SolidObj*, HitBox*) = 0;
public:
	Vec3f	velocity;
};

#endif

