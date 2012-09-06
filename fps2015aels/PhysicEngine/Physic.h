#ifndef __PHYSIC_H__
#define __PHYSIC_H__

#include <GL/glut.h>
#include "Octree.h"
#include "../Objects/StaticObj.h"
#include "../Objects/NewtonObj.h"
#include "../Objects/Plane.h"

class	Physic
{
public:
		Physic(Camera*);
	virtual ~Physic(void);
	void	AdvanceWorld(GLfloat&);
	void	AddObject(SolidObj*);
	void	AddObject(Plane*);
	void	AddObject(StaticObj*);
	void	DelObject(SolidObj*);
	void	Update(void);
	void	MoveWorld(GLfloat);
private:
	void	__ApplyGravity(void);
	bool	__CheckCollision(SolidObj*, SolidObj*);
	void	__ApplyCollision(void);
private:
	Octree			__octree;
	std::vector<NewtonObj*>	__newton_objs;
	std::vector<SolidObj*>	__solid_objs;
	size_t			__nb_newton_objs;
	Camera*			__camera;
};

#endif

