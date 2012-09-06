#ifndef __SUN_H__
#define __SUN_H__

#include <GL/glut.h>
#include "Light.h"

class	Sun : public Light
{
public:
		Sun(Vec3f rot = Vec3f(0.f, 0.f, 0.f),
		    GLfloat r = 1.f, GLfloat g = 1.f,
		    GLfloat b = 1.f, GLfloat a = 1.f);
	virtual	~Sun(void);
private:

};

#endif

