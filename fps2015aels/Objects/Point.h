#ifndef Point_h
#define Point_h
#include "Vec3f.h"
#include "Vec2f.h"

class	Point
{
	public:
		Point();
		Point(Vec3f P);
		Point(float x, float y, float z);
		Point(float x, float y, float z, float n1, float n2, float n3);
		Point(float x, float y, float z, float n1, float n2, float n3, float U, float V);
		Point(Vec3f P, Vec3f N);
		Point(Vec3f P, Vec3f N, Vec2f UV);

		#include "PointInline.hpp"
		~Point();
	private:
		Vec3f	P;
		Vec3f	N;
		Vec2f	UV;
};

#endif
