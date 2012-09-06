#ifndef __OCTREE_H__
#define __OCTREE_H__

#include <set>
#include <list>
#include "../Objects/SolidObj.h"
#include "../Objects/Vec3f.h"

#define MAX_OCTREE_DEPTH	6
#define MIN_OBJ_PER_OCTREE	2
#define	MAX_OBJ_PER_OCTREE	5

struct	ObjectPair
{
	SolidObj*	o1;
	SolidObj*	o2;
	HitBox*		h1;
	HitBox*		h2;
};

class	Octree
{
public:
		Octree(Vec3f, Vec3f, int);
	virtual ~Octree(void);
public:
	void	Add(SolidObj*);
	void	Add(HitBox*);
	void	Remove(SolidObj*);
	void	Move(SolidObj*);
	void	Move(HitBox*, Vec3f);
	void	CheckCollision(std::list<ObjectPair>*);
private:
	void	__FileObject(HitBox*, Vec3f, bool);
	void	__CreateChild(void);
	void	__CollectObject(std::list<HitBox*>*);
	void	__DestroyChild(void);
	void	__Remove(HitBox*, Vec3f);
private:
	Vec3f			__corner_min;
	Vec3f			__corner_max;
	Vec3f			__center;
	Octree*			__child[2][2][2];
	bool			__has_child;
	std::list<HitBox*>	__objects;
	int			__depth;
	int			__nb_objs;
};

#endif

