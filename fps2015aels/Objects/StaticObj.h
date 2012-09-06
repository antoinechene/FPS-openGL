#ifndef __STATICOBJ_H__
#define __STATICOBJ_H__

#include "SolidObj.h"
#include "Ball.h"

class Ball;
class HitBox;
class	StaticObj : public SolidObj
{
public:
			StaticObj();
			StaticObj(Vec3f, Vec3f, Vec3f);
			~StaticObj(void);
			virtual bool	GenerateHitBox(void);
			virtual void	Collision(HitBox*, SolidObj*, HitBox*);
			void		AddHitbox(HitBox* hit);
			void		DrawHitbox(void);

private:
	bool	__TestSphereCollision(HitBox*, Ball*);
	void	__ApplySphereCollision(Ball*);
public:
	int	impact;
};

#endif

