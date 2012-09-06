#include "Octree.h"

Octree::Octree(Vec3f cmin, Vec3f cmax, int dep) : __corner_min(cmin), __corner_max(cmax),
						   __center((cmin + cmax) / 2), __has_child(false),
						   __depth(dep), __nb_objs(0)
{

}

Octree::~Octree(void)
{
	if (this->__has_child)
		this->__DestroyChild();
}

void	Octree::Add(SolidObj* obj)
{
	std::list<HitBox*>*		hits = obj->GetHitboxes();
	std::list<HitBox*>::iterator	it = hits->begin();
	std::list<HitBox*>::iterator	it_end = hits->end();
		
	while (it != it_end)
	{
		this->Add(*it);
		++it;
	}
}

void	Octree::Add(HitBox* obj)
{
	++this->__nb_objs;
	if (!this->__has_child &&
	    this->__depth < MAX_OCTREE_DEPTH &&
	    this->__nb_objs > MAX_OBJ_PER_OCTREE)
		this->__CreateChild();

	if (this->__has_child)
		this->__FileObject(obj, obj->__pos, true);
	else
		this->__objects.insert(this->__objects.begin(), obj);
	
}

void	Octree::Remove(SolidObj* obj)
{
	std::list<HitBox*>*		hits = obj->GetHitboxes();
	std::list<HitBox*>::iterator	it = hits->begin();
	std::list<HitBox*>::iterator	it_end = hits->end();

	while (it != it_end)
	{
		this->__Remove((*it), (*it)->__pos);
		++it;
	}
}

void	Octree::Move(HitBox* obj, Vec3f old_pos)
{
	this->__Remove(obj, old_pos);
	this->Add(obj);
}

void	Octree::Move(SolidObj* obj)
{
	std::list<HitBox*>*		hits = obj->GetHitboxes();
	std::list<HitBox*>::iterator	it = hits->begin();
	std::list<HitBox*>::iterator	it_end = hits->end();

	while (it != it_end)
	{
		this->Move((*it), (*it)->__pos);
		++it;
	}
}

void	Octree::CheckCollision(std::list<ObjectPair>* obj_pairs)
{
	if (this->__has_child)
	{
		this->__child[0][0][0]->CheckCollision(obj_pairs);
		this->__child[0][0][1]->CheckCollision(obj_pairs);
		this->__child[0][1][0]->CheckCollision(obj_pairs);
		this->__child[0][1][1]->CheckCollision(obj_pairs);
		this->__child[1][0][0]->CheckCollision(obj_pairs);
		this->__child[1][0][1]->CheckCollision(obj_pairs);
		this->__child[1][1][0]->CheckCollision(obj_pairs);
		this->__child[1][1][1]->CheckCollision(obj_pairs);
	}
	else
	{
		ObjectPair			op;
		std::list<HitBox*>::iterator	it = this->__objects.begin();
		std::list<HitBox*>::iterator	it2;
		std::list<HitBox*>::iterator	it_end = this->__objects.end();

		while (it != it_end)
		{
			it2 = it;
			++it2;
			while (it2 != it_end)
			{
				if ((*it)->__parent == (*it2)->__parent)
				{
					++it2;
					continue;
				}
				op.o1 = (*it)->__parent;
				op.o2 = (*it2)->__parent;
				op.h1 = *it;
				op.h2 = *it2;
				obj_pairs->push_back(op);
				++it2;
			}
			++it;
		}
	}
}

void	Octree::__FileObject(HitBox* obj, Vec3f pos, bool add)
{
	int	x;
	int	y;
	int	z;

	x = 0;
	while (x < 2)
	{
		if (x == 0)
		{
			if (pos[0] - obj->__size > this->__center[0])
			{
				++x;
				continue;
			}
		}
		else if (pos[0] + obj->__size < this->__center[0])
		{
			++x;
			continue;
		}
		y = 0;
		while (y < 2)
		{
			if (y == 0)
			{
				if (pos[1] - obj->__size > this->__center[1])
				{
					++y;
					continue;
				}
			}
			else if (pos[1] + obj->__size < this->__center[1])
			{
				++y;
				continue;
			}
			z = 0;
			while (z < 2)
			{
				if (z == 0)
				{
					if (pos[2] - obj->__size > this->__center[2])
					{
						++z;
						continue;
					}
				}
				else if (pos[2] + obj->__size < this->__center[2])
				{
					++z;
					continue;
				}
				if (add)
					this->__child[x][y][z]->Add(obj);
				else
					this->__child[x][y][z]->__Remove(obj, pos);
				++z;
			}
			++y;
		}
		++x;
	}
}

void	Octree::__CreateChild(void)
{
	int				x;
	int				y;
	int				z;
	Vec3f				min;
	Vec3f				max;
	std::list<HitBox*>::iterator	it;
	std::list<HitBox*>::iterator	it_end;

	x = 0;
	while (x < 2)
	{
		if (x == 0)
		{
			min[0] = this->__corner_min[0];
			max[0] = this->__center[0];
		}
		else
		{
			min[0] = this->__center[0];
			max[0] = this->__corner_max[0];
		}
		y = 0;
		while (y < 2)
		{
			if (y == 0)
			{
				min[1] = this->__corner_min[1];
				max[1] = this->__center[1];
			}
			else
			{
				min[1] = this->__center[1];
				max[1] = this->__corner_max[1];
			}
			z = 0;
			while (z < 2)
			{
				if (z == 0)
				{
					min[2] = this->__corner_min[2];
					max[2] = this->__center[2];
				}
				else
				{
					min[2] = this->__center[2];
					max[2] = this->__corner_max[2];
				}
				this->__child[x][y][z] = new Octree(Vec3f(min[0], min[1], min[2]),
								    Vec3f(max[0], max[1], max[2]),
								    this->__depth + 1);
				++z;
			}
			++y;
		}
		++x;
	}
	it = this->__objects.begin();
	it_end = this->__objects.end();
	while (it != it_end)
	{
		this->__FileObject(*it, (*it)->__pos, true);
		++it;
	}
	this->__objects.clear();
	this->__has_child = true;

}

void	Octree::__CollectObject(std::list<HitBox*>* objs)
{
	if (this->__has_child)
	{
		this->__child[0][0][0]->__CollectObject(objs);
		this->__child[0][0][1]->__CollectObject(objs);
		this->__child[0][1][0]->__CollectObject(objs);
		this->__child[0][1][1]->__CollectObject(objs);
		this->__child[1][0][0]->__CollectObject(objs);
		this->__child[1][0][1]->__CollectObject(objs);
		this->__child[1][1][0]->__CollectObject(objs);
		this->__child[1][1][1]->__CollectObject(objs);
	}
	else
	{
		std::list<HitBox*>::iterator	it = this->__objects.begin();
		std::list<HitBox*>::iterator	it_end = this->__objects.end();

		while (it != it_end)
		{
			objs->insert(objs->begin(), *it);
			++it;
		}
	}
}

void	Octree::__DestroyChild(void)
{
	this->__CollectObject(&this->__objects);
	delete this->__child[0][0][0];
	delete this->__child[0][0][1];
	delete this->__child[0][1][0];
	delete this->__child[0][1][1];
	delete this->__child[1][0][0];
	delete this->__child[1][0][1];
	delete this->__child[1][1][0];
	delete this->__child[1][1][1];
	this->__has_child = false;
}

void	Octree::__Remove(HitBox* obj, Vec3f pos)
{
	--this->__nb_objs;
	if (this->__has_child && this->__nb_objs < MIN_OBJ_PER_OCTREE)
		this->__DestroyChild();
	if (this->__has_child)
		this->__FileObject(obj, pos, false);
	else
		this->__objects.remove(obj);
}

