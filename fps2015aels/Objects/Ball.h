#ifndef __BALL_H__
#define __BALL_H__

#include <GL/glut.h>
#include "NewtonObj.h"
#include "Camera.h"
#include "StaticObj.h"

class Camera;
class StaticObj;

class	Ball : public NewtonObj
{
public:
			Ball(Vec3f pos = Vec3f(0.f, 0.f, 0.f),
			     Vec3f rot = Vec3f(0.f, 0.f, 0.f),
			     Vec3f sca = Vec3f(1.f, 1.f, 1.f),
			     Vec3f vel = Vec3f(0.f, 0.f, 0.f),
			     GLfloat mas = 1.f, GLfloat rad = 1.f);
	virtual		~Ball(void);
	virtual bool	GenerateHitBox(void);
	virtual void	Collision(HitBox*, SolidObj*, HitBox*);
private:
	bool	__TestSphereCollision(Ball*);
	bool	__TestCameraCollision(Camera*);
	bool	__TestStaticObjCollision(HitBox*, StaticObj*);
	void	__ApplySphereCollision(Ball*);
	void	__ApplyCameraCollision(Camera*);
	void	__ApplyStaticObjCollision(StaticObj*);
public:
	GLfloat	radius;
	int	impact;
protected:

private:

};

#endif

