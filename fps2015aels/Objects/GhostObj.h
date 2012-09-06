#ifndef __GHOSTOBJ_H__
#define __GHOSTOBJ_H__

#include "Object.h"
#include "Vec3f.h"

class	GhostObj : public Object
{
public:
			GhostObj(Vec3f, Vec3f, Vec3f);
	virtual		~GhostObj(void);
};

#endif

