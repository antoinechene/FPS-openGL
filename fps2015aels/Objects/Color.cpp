#include "Color.h"

Color::Color()
{
	this->R = 0.0f;
	this->G = 0.0f;
	this->B = 0.0f;
}
Color::Color(int r, int g, int b)
{
	this->R = r;
	this->G = g;
	this->B = b;
}

Color::Color(KFbxPropertyDouble3 col)
{
	this->R = col.Get()[0];
	this->G = col.Get()[1];
	this->B = col.Get()[2];
}

Color::~Color()
{
}

