#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "NewtonObj.h"
#include "Vec3f.h"
#include "Ball.h"

class Ball;

class	Camera : public NewtonObj
{
public:
		Camera(Vec3f pos = Vec3f(0.f, 5.f, 0.f),
		       Vec3f rot = Vec3f(0.f, 0.f, 0.f),
		       Vec3f scale = Vec3f(1.f, 1.f, 1.f),
		       Vec3f velocity = Vec3f(0.f, 0.f, 0.f),
		       GLfloat m = 50.f,
		       Vec3f t = Vec3f(0.f, 1.f, 0.f),
		       Vec3f f = Vec3f(1.f, 0.f, 0.f),
		       Vec3f l = Vec3f(0.f, 0.f, -1.f),
		       GLfloat fov = 45.f,
		       GLfloat near = 0.1f,
		       GLfloat far = 2000.f,
		       GLfloat width = 800.f,
		       GLfloat height = 600.f,
		       GLfloat speed_forward = 25.f,
		       GLfloat speed_side = 25.f,
		       GLfloat sensitivityx = 0.02f,
		       GLfloat sensitivityy = 0.015f,
		       GLfloat phi = 0.f,
		       GLfloat theta = 0.f,
		       bool jumping = false);//,
//		       Vec3f radius = Vec3f(3.f, 7.f, 3.f));
	virtual	~Camera(void);
	virtual bool	GenerateHitBox(void);
	virtual void	Collision(HitBox*, SolidObj*, HitBox*);
private:
	bool	__TestSphereCollision(Ball*);
	void	__ApplySphereCollision(Ball*);
public:
	Vec3f	target;
	Vec3f	forward;
	Vec3f	left;
	GLfloat	fov;
	GLfloat	near;
	GLfloat	far;
	GLfloat	width;
	GLfloat	height;
	GLfloat	speed_forward;
	GLfloat	speed_side;
	GLfloat	sensitivityx;
	GLfloat	sensitivityy;
	GLfloat	phi;
	GLfloat	theta;
	bool	jumping;
	Vec3f	radius;
};

#endif

