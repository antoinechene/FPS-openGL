#ifndef __PLANE_H__
#define __PLANE_H__

#include <GL/glut.h>
#include "StaticObj.h"
#include "Ball.h"
#include "Camera.h"

class	Plane : public StaticObj
{
public:
		Plane(Vec3f p = Vec3f(0.f, 0.f, 0.f),
		      Vec3f r = Vec3f(0.f, 0.f, 0.f),
		      Vec3f s = Vec3f(1.f, 1.f, 1.f),
		      GLfloat height = 10.f,
		      GLfloat width = 10.f);
	virtual ~Plane(void);
	void	Collision(SolidObj*);
	bool	GenerateHitBox(void);
private:
	bool	__TestSphereCollision(Ball*);
	bool	__TestCameraCollision(Camera*);
	void	__ApplySphereCollision(Ball*);
	void	__ApplyCameraCollision(Camera*);
public:
	GLfloat	height;
	GLfloat	width;
};

#endif

