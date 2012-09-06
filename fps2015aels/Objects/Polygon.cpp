#include "Polygon.h"


Polygon::Polygon()
{
}

Polygon::Polygon(size_t size)
{
	this->Mesh = new Point*[size + 1];
	this->UV = new Vec2f*[size];
	this->size = size;
}

Polygon::~Polygon()
{
}
