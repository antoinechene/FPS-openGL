#ifndef __HITBOX_H__
#define __HITBOX_H__

#include <GL/glut.h>
#include "Vec3f.h"
#include "SolidObj.h"

class SolidObj;

class	HitBox
{
public:
		HitBox(GLfloat, Vec3f, SolidObj*, int);
	virtual ~HitBox(void);
	inline GLfloat	GetSize(void)
	{
		return (this->__size);
	}
//private:
	GLfloat		__size;
	Vec3f		__pos;
	SolidObj*	__parent;
	int		__id;
};

#endif

