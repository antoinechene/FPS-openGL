#ifndef __NEWTONOBJ_H__
#define __NEWTONOBJ_H__

#include <GL/glut.h>
#include "PhysObj.h"

class	NewtonObj : public PhysObj
{
public:
			NewtonObj(Vec3f, Vec3f, Vec3f, Vec3f, GLfloat);
	virtual		~NewtonObj(void);
	virtual bool	GenerateHitBox(void) = 0;
	virtual void	Collision(HitBox*, SolidObj*, HitBox*) = 0;
public:
	GLfloat	mass;
};

#endif

