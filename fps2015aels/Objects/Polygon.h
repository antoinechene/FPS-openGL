#ifndef Polygon_h
#define Polygon_h
#include "Point.h"

class Polygon
{
	public:
		Polygon();
		Polygon(size_t size);

		~Polygon();
	public:
		Point**	Mesh;
		Vec2f**	UV;
		size_t	size;
};

#endif
