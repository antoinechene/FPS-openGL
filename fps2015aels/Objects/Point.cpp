#include "Point.h"


Point::Point()
{
}

Point::Point(Vec3f P)
{
	this->P = P;
}

Point::Point(Vec3f P, Vec3f N)
{
	this->P = P;
	this->N = N;
}
Point::Point(float x, float y, float z)
{
	this->P[0] = x;
	this->P[1] = y;
	this->P[2] = z;

}

Point::Point(float x, float y, float z, float n1, float n2, float n3)
{
	this->P[0] = x;
	this->P[1] = y;
	this->P[2] = z;

	this->N[0] = n1;
	this->N[1] = n2;
	this->N[2] = n3;

}
Point::Point(float x, float y, float z, float n1, float n2, float n3, float U, float V)
{
	this->P[0] = x;
	this->P[1] = y;
	this->P[2] = z;

	this->N[0] = n1;
	this->N[1] = n2;
	this->N[2] = n3;

	this->UV[0] = U;
	this->UV[1] = V;

}

Point::Point(Vec3f P, Vec3f N, Vec2f UV)
{
	this->P = P;
	this->N = N;
	this->UV = UV;
}

Point::~Point()
{
}
