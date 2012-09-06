#ifndef __SPOT_H__
#define __SPOT_H__

#include "Light.h"

class	Spot : public Light
{
public:
		Spot(Vec3f rot = Vec3f(0.f, 0.f, 0.f),
		     GLfloat r = 1.f, GLfloat g = 1.f,
		     GLfloat b = 1.f, GLfloat a = 1.f);
	virtual	~Spot(void);
protected:

private:

};

#endif

