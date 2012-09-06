#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <GL/glut.h>
#include "GhostObj.h"

class	Light : public GhostObj
{
public:
		Light(Vec3f pos = Vec3f(0.f, 0.f, 0.f),
		      Vec3f rot = Vec3f(0.f, 0.f, 0.f),
		      Vec3f sca = Vec3f(1.f, 1.f, 1.f),
		      GLfloat r = 1.f, GLfloat g = 1.f,
		      GLfloat b = 1.f, GLfloat a = 1.f);
	virtual	~Light(void);
public:
	GLfloat	color[4];
};

#endif

