#ifndef __SOLIDOBJ_H__
#define __SOLIDOBJ_H__

#include <GL/glut.h>
#include <list>
#include "Object.h"
#include "HitBox.h"

class HitBox;

class	SolidObj : public Object
{
public:
			SolidObj();
			SolidObj(Vec3f, Vec3f, Vec3f);
	virtual		~SolidObj(void);
//	virtual bool	GenerateHitBox(void);
	inline GLfloat	GetHitboxSize(void)
	{
		return (1.0f);
//		return (this->_hitbox->GetSize());
	}
	virtual void	Collision(HitBox*, SolidObj*, HitBox*);
	inline std::list<HitBox*>*	GetHitboxes(void)
	{
		return (&this->_hitbox);
	}

	std::list<HitBox*>	_hitbox;
};

#endif

